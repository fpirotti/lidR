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



#' An S4 class to represent the data read in a .las or .laz file
#'
#' A LAS object contains the data and the header read in a .las file and
#' additional values computed on the fly during the loading.
#'
#' A \code{LAS} object contains a \code{data.table} in the slot \code{@data} with
#' the data read from a \code{.las} file and other information computed during
#' data loading. The fields read from the las file are named:
#' \itemize{
#' \item{\code{X Y Z}}
#' \item{\code{Intensity}}
#' \item{\code{ReturnNumber}}
#' \item{\code{NumberOfReturns}}
#' \item{\code{ScanDirectionFlag}}
#' \item{\code{EdgeofFlightline}}
#' \item{\code{Classification}}
#' \item{\code{ScanAngle}}
#' \item{\code{UserData}}
#' \item{\code{PointSourceID}}
#' }
#' When a \code{LAS} object is built, two other variables are computed in the
#' slot \code{@data}:
#' \itemize{
#' \item{\code{pulseID}: }{a unique identifying number for each pulse so the
#' beam origin of each point is known}
#'
#' \item{\code{flightlineID}: }{a unique identifying number for the flightline
#' so the flightline origin of each point is known}
#' }
#'
#' A \code{LAS} object contains other information in slots \code{@area},
#' \code{@pointDensity} and \code{@pulseDensity}:
#' \itemize{
#' \item{\code{area}: }{is computed with a convex hull. It is only an
#' approximation if the shape of the data is not convex.}
#'
#' \item{\code{points} and \code{pulse density}: }{are computed using the
#' computed area. Also an approximation if the data are not convex}
#' }
#'
#' A \code{LAS} object also contains a slot \code{@header} which contains the
#' header of the \code{.las} file. See the public documentation of LAS
#' specifications of file format for more informations.
#'
#' @slot data data.table. a table representing the LAS data
#' @slot area numeric. The area of the dataset computed with a convex hull
#' @slot pointDensity numeric. The point density of the dataset
#' @slot pulseDensity numeric. The pulse density of the dataset
#' @slot header list. A list of information contained in the las file header.
#' @seealso
#' \link[lidR:LAS]{LAS}
#' @name LAS-class
#' @rdname LAS-class
#' @exportClass LAS
#' @import dtplyr
#' @importFrom methods new
#' @importFrom grDevices rgb
#' @importFrom magrittr %>% %$% divide_by
#' @importFrom dplyr n_distinct
setClass(
	Class = "LAS",
	representation(
		data 					= "data.table",
		area 					= "numeric",
		pointDensity 	= "numeric",
		pulseDensity 	= "numeric",
		header        = "list"
	)
)

#' @importFrom data.table is.data.table setorder
setMethod("initialize", "LAS",
	function(.Object, data, header = list())
	{
	  gpstime <- R <- G <- B <- X <- Y <- NULL

	  if(!is.data.table(data))
	    lidRError("LDR1")

	  if(dim(data)[1] == 0)
	    lidRError("LDR9")

	  # Check if the data are valid. Else: warning -------------------------------

	  negvalues = sum(data$Z < 0)
	  if(negvalues > 0)
	    lidRError("LDR2", number = negvalues, behaviour = warning)

	  if("Classification" %in% names(data))
	  {
	    class0 = sum(data$Classification == 0)
	    if(class0 > 0)
	      lidRError("LDR3", number = class0, behaviour = warning)
	  }

	  # Compute extra data -------------------------------------------------------

	  fields <- names(data)
	  area   <- data %$% area(X, Y)
	  dpoint <- data %>% nrow %>% divide_by(area) %>% round(2)
	  dpulse <- NA_real_

	  if("gpstime" %in% fields)
	  {
  	  setorder(data, gpstime)

  	  if (!"pulseID" %in% fields & "ReturnNumber" %in% fields)
  	  {
  	    data$pulseID <- .identify_pulse(data$ReturnNumber)
  	    dpulse <- data$pulseID %>% n_distinct %>% divide_by(area) %>% round(2)
  	  }
	    else if (!"pulseID" %in% fields & !"ReturnNumber" %in% fields)
	    {
	      lidRError("LDR8", behaviour = message)
	    }
      else if ("pulseID" %in% fields)
      {
	      dpulse <- data$pulseID %>% n_distinct %>% divide_by(area) %>% round(2)
      }

  	  if(!"flightlineID" %in% fields)
  	  {
  	    data$flightlineID <- .identify_flightlines(data$gpstime)
  	  }
	  }
	  else
	  {
	    lidRError("LDR4", behaviour = message)
	  }

	  if(sum(c("R", "G", "B") %in% names(data)) == 3)
	  {
	    if(is.null(data$color))
  	    data$color <- data %$% grDevices::rgb(R/65535, G/65535, B/65535)
	  }

	  # Update header ------------------------------------------------------------

	  header["Min X"] = min(data$X)
	  header["Min Y"] = min(data$Y)
	  header["Min Z"] = min(data$Z)
	  header["Max X"] = max(data$X)
	  header["Max Y"] = max(data$Y)
	  header["Max Z"] = max(data$Z)

	  # Build returned object  ---------------------------------------------------

	  .Object@data         <- data
	  .Object@header       <- header
	  .Object@area         <- area
	  .Object@pointDensity <- dpoint
	  .Object@pulseDensity <- dpulse

	  return(.Object)
	}
)

#' Extract parts of a LAS object
#'
#' @param x object from which to extract element(s).
#' @param name A literal character string or a name (possibly backtick quoted).
#' @importFrom methods slot slotNames
setMethod("$", "LAS", function(x, name)
{
  if(name %in% names(x@data))
    return(as.numeric(unlist(x@data[,name,with=F])))
  else if(name %in% slotNames(x))
    return(slot(x, name))
  else if(name %in% names(x@header))
    return(x@header[name])
})
