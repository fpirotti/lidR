# ===============================================================================
#
# PROGRAMMERS:
#
# jean-romain.roussel.1@ulaval.ca  -  https://github.com/Jean-Romain/lidR
#
# COPYRIGHT:
#
# Copyright 2016 Jean-Romain Roussel
#
# This file is part of lidR R package.
#
# lidR is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# ===============================================================================

#' Canopy height model based on a triangular irregular network.
#'
#' Interpolation of a triangular irregular network constructed from first returns. This function
#' enables use of the pit-free algorithm developed by Khosravipour et al. (see reference).
#'
#'
#' @param .las A LAS object
#' @param res numeric resolution
#' @param thresholds numeric array. Set of height threholds. If \code{thresholds = 0} the algorithm
#' is a strict rasterizaton of the triangulation of the first returns. However, if an array is passed to
#' the function it becomes the Khosravipour et al. pit-free algorithm.
#' @param max_edge  numeric. Maximum edge-length of a triangle in the Delaunay triangulation
#' used to constrain the pit-free algorithm (see reference).
#' @param subcircle numeric radius of the circles. To obtain fewer pits the algorithm
#' can replace each return with a circle composed of 8 points before computing the triangulation.
#' @return An object of class \code{lasmetrics}
#' @export
#' @examples
#' LASfile <- system.file("extdata", "Tree.laz", package="lidR")
#' las = readLAS(LASfile, Classification = FALSE, Intensity = FALSE, filter = "-drop_z_below 0")
#'
#' # Basic triangulation and rasterization
#' chm1 = grid_tincanopy(las, thresholds = 0)
#'
#' # Khosravipour et al. pitfree algorithm
#' chm2 = grid_tincanopy(las, thresholds = c(0,2,5,10,15), max_edge = 1.5)
#'
#' plot(chm1)
#' plot(chm2)
#' @references Khosravipour, A., Skidmore, A. K., Isenburg, M., Wang, T., & Hussin, Y. A. (2014).
#' Generating pit-free canopy height models from airborne lidar. Photogrammetric Engineering &
#' Remote Sensing, 80(9), 863-872.
grid_tincanopy = function(.las, res = 0.5, thresholds =  c(0,2,5,10,15), max_edge = 1, subcircle = 0)
{
  . <- X <- Y <- Z <- ReturnNumber <- Xgrid <- Ygrid <- NULL

  if (!"ReturnNumber" %in% names(.las@data))
     stop("No column 'ReturnNumber' found. This fields is needed to extract first returns", call. = FALSE)

  if (fast_countequal(.las@data$ReturnNumber, 1) == 0)
    stop("No first returns found. Aborded.", call. = FALSE)

  if (length(thresholds) == 1 & thresholds[1] == 0)
    cat("[Delaunay triangulation of first returns]")
  else if (length(thresholds) > 1)
    cat("[Khosravipour et al. pitfree algorithm]")

  # Create the coordinates of interpolation (pixel coordinates)
  ex = extent(.las)
  grid = make_grid(ex@xmin, ex@xmax, ex@ymin, ex@ymax, res)

  # Initialize the interpolated values with NAs
  z = rep(NA, (dim(grid)[1]))

  # Get only first returns and coordinates (nothing else needed)
  cloud = .las@data[ReturnNumber == 1, .(X,Y,Z)]

  # subcircled the data
  if (subcircle > 0)
  {
    ex = extent(.las)
    cloud = subcircled(cloud, subcircle, 8)
    cloud = cloud[between(X, ex@xmin, ex@xmax) & between(Y, ex@ymin, ex@ymax)]
  }

  # Select only the highest points within the grid cells (reduce the computations)
  f = function(x,y,z) {
    i = which.max(z)
    return(list(X = x[i], Y = y[i], Z = z[i]))
  }

  by = group_grid(cloud$X, cloud$Y, res)
  cloud = cloud[, f(X,Y,Z), by = by][, Xgrid := NULL][, Ygrid := NULL][]

  # Perform the triangulation and the rasterization (1 loop for classical triangulation, several for Khosravipour)
  for (th in thresholds)
  {
    if (th == 0)
      edge = 0
    else
      edge = max_edge

    pts = cloud[Z >= th]
    Ztemp = interpolate_delaunay(pts, grid, edge)
    z = pmax(z, Ztemp, na.rm = T)
  }

  grid[, Z := z][]
  as.lasmetrics(grid,res)

  return(grid)
}