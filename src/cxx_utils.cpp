/*
===============================================================================

PROGRAMMERS:

jean-romain.roussel.1@ulaval.ca  -  https://github.com/Jean-Romain/lidR

COPYRIGHT:

Copyright 2016 Jean-Romain Roussel

This file is part of lidR R package.

lidR is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>

===============================================================================
*/

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
IntegerVector fast_table(IntegerVector x, int size = 5)
{
  IntegerVector tbl(size);

  for (IntegerVector::iterator it = x.begin(), end = x.end() ; it != end ; ++it)
  {
    if (*it <= size && *it > 0)
      tbl(*it-1)++;
  }

  return tbl;
}

// [[Rcpp::export]]
int fast_countequal(NumericVector x, double t)
{
  int n = 0;

  for (NumericVector::iterator it = x.begin(), end = x.end() ; it != end ; ++it)
  {
    if (*it == t)
      n++;
  }

  return n;
}

// [[Rcpp::export]]
int fast_countbelow(NumericVector x, double t)
{
  int n = 0;

  for (NumericVector::iterator it = x.begin(), end = x.end() ; it != end ; ++it)
  {
    if (*it < t)
      n++;
  }

  return n;
}

// [[Rcpp::export]]
int fast_countover(NumericVector x, double t)
{
  int n = 0;

  for (NumericVector::iterator it = x.begin(), end = x.end() ; it != end ; ++it)
  {
    if (*it > t)
      n++;
  }

  return n;
}

// @param M a matrix n x 4 describing a delaunay triangulation. Each row a set of indices to the points + a triangle id
// This matrix is expected to be pruned of useless triangles in attempt to reduce the computation times
// @param X a matrix m x 3 with the points coordinates
// @param size the number of triangle in original dataset
// @return n x 6 matrix with 3 coord of normal vector, intercept, area, projected area, max edge size
// [[Rcpp::export]]
NumericMatrix triangle_information(IntegerMatrix M, NumericMatrix X)
{
  NumericMatrix N(M.nrow(), 7);
  std::fill(N.begin(), N.end(), NA_REAL);

  for (int i = 0, end = M.nrow() ; i < end ; i++)
  {
    int p1 = M(i,0)-1;
    int p2 = M(i,1)-1;
    int p3 = M(i,2)-1;

    NumericVector A = NumericVector::create(X(p1,0), X(p1,1), X(p1,2));
    NumericVector B = NumericVector::create(X(p2,0), X(p2,1), X(p2,2));
    NumericVector C = NumericVector::create(X(p3,0), X(p3,1), X(p3,2));

    NumericVector u = A - B;
    NumericVector v = A - C;
    NumericVector w = B - C;

    // Cross product
    NumericVector n(3);
    n(0) = u(1)*v(2)-u(2)*v(1);
    n(1) = u(2)*v(0)-u(0)*v(2);
    n(2) = u(0)*v(1)-u(1)*v(0);

    // normal vector
    N(i,0) = n(0);
    N(i,1) = n(1);
    N(i,2) = n(2);

    // intercept
    N(i,3) = sum(-n*C);

    // area and projected area
    N(i,4) = 0.5 * sqrt(n(0) * n(0) + n(1) * n(1) + n(2) * n(2));
    N(i,5) = 0.5 * n(2);

    // max edge length
    u.erase(2);
    v.erase(2);
    w.erase(2);
    NumericVector e = NumericVector::create(sqrt(sum(pow(u, 2))), sqrt(sum(pow(v, 2))), sqrt(sum(pow(w, 2))));
    N(i,6) = max(e);
  }

  colnames(N) = CharacterVector::create("nx", "ny", "nz", "intercept", "xyzarea", "xyarea", "maxedge");

  return N;
}

IntegerMatrix which_equal(IntegerMatrix mtx, double val)
{
  int l = mtx.nrow();
  int w = mtx.ncol();

  NumericVector x;
  NumericVector y;

  for(int i = 0 ; i < l ; i++)
  {
    for(int j = 0 ; j < w ; j++)
    {
      if(mtx(i,j) == val)
      {
        x.push_back(i);
        y.push_back(j);
      }
    }
  }

  IntegerMatrix m(x.length(), 2);
  m(_, 0) = x;
  m(_, 1) = y;

  return(m);
}

NumericVector filter_xx(NumericMatrix x, IntegerMatrix y)
{
  int nrow = y.nrow();
  NumericVector out(nrow);

  for(int i = 0 ; i < nrow ; i++)
    out(i) = x(y(i,0), y(i,1));

  return(out);
}

NumericVector sqdistance(NumericVector x1, NumericVector y1, double x2, double y2)
{
  int n = x1.length();
  NumericVector y(n);
  NumericVector::iterator i1, i2, i3, end1, end2, end3;

  for( i1 = x1.begin(), i2 = y1.begin(), i3 = y.begin(), end1 = x1.end(), end2 = y1.end(), end3 = y.end();
       i1 < end1 && i2 < end2 && i3 < end3;
        ++i1, ++i2 , ++i3)
  {
    double dx = *i1-x2;
    double dy = *i2-y2;
    *i3 = dx * dx + dy * dy;
  }

  return y;
}

