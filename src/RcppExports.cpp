// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// itc_treetops
IntegerMatrix itc_treetops(NumericMatrix Canopy, double searchWinSize);
RcppExport SEXP lidR_itc_treetops(SEXP CanopySEXP, SEXP searchWinSizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type Canopy(CanopySEXP);
    Rcpp::traits::input_parameter< double >::type searchWinSize(searchWinSizeSEXP);
    rcpp_result_gen = Rcpp::wrap(itc_treetops(Canopy, searchWinSize));
    return rcpp_result_gen;
END_RCPP
}
// itc_expandcrowns
IntegerMatrix itc_expandcrowns(NumericMatrix Canopy, IntegerMatrix Maxima, double TRESHSeed, double TRESHCrown, double DIST);
RcppExport SEXP lidR_itc_expandcrowns(SEXP CanopySEXP, SEXP MaximaSEXP, SEXP TRESHSeedSEXP, SEXP TRESHCrownSEXP, SEXP DISTSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type Canopy(CanopySEXP);
    Rcpp::traits::input_parameter< IntegerMatrix >::type Maxima(MaximaSEXP);
    Rcpp::traits::input_parameter< double >::type TRESHSeed(TRESHSeedSEXP);
    Rcpp::traits::input_parameter< double >::type TRESHCrown(TRESHCrownSEXP);
    Rcpp::traits::input_parameter< double >::type DIST(DISTSEXP);
    rcpp_result_gen = Rcpp::wrap(itc_expandcrowns(Canopy, Maxima, TRESHSeed, TRESHCrown, DIST));
    return rcpp_result_gen;
END_RCPP
}
// algo_li2012
IntegerVector algo_li2012(NumericVector X, NumericVector Y, const NumericVector Z, double dt1, double dt2, double R);
RcppExport SEXP lidR_algo_li2012(SEXP XSEXP, SEXP YSEXP, SEXP ZSEXP, SEXP dt1SEXP, SEXP dt2SEXP, SEXP RSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type X(XSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type Y(YSEXP);
    Rcpp::traits::input_parameter< const NumericVector >::type Z(ZSEXP);
    Rcpp::traits::input_parameter< double >::type dt1(dt1SEXP);
    Rcpp::traits::input_parameter< double >::type dt2(dt2SEXP);
    Rcpp::traits::input_parameter< double >::type R(RSEXP);
    rcpp_result_gen = Rcpp::wrap(algo_li2012(X, Y, Z, dt1, dt2, R));
    return rcpp_result_gen;
END_RCPP
}
// fast_table
IntegerVector fast_table(IntegerVector x, int size);
RcppExport SEXP lidR_fast_table(SEXP xSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(fast_table(x, size));
    return rcpp_result_gen;
END_RCPP
}
// fast_countequal
int fast_countequal(NumericVector x, double t);
RcppExport SEXP lidR_fast_countequal(SEXP xSEXP, SEXP tSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type t(tSEXP);
    rcpp_result_gen = Rcpp::wrap(fast_countequal(x, t));
    return rcpp_result_gen;
END_RCPP
}
// fast_countbelow
int fast_countbelow(NumericVector x, double t);
RcppExport SEXP lidR_fast_countbelow(SEXP xSEXP, SEXP tSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type t(tSEXP);
    rcpp_result_gen = Rcpp::wrap(fast_countbelow(x, t));
    return rcpp_result_gen;
END_RCPP
}
// fast_countover
int fast_countover(NumericVector x, double t);
RcppExport SEXP lidR_fast_countover(SEXP xSEXP, SEXP tSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type t(tSEXP);
    rcpp_result_gen = Rcpp::wrap(fast_countover(x, t));
    return rcpp_result_gen;
END_RCPP
}
// triangle_information
NumericMatrix triangle_information(IntegerMatrix M, NumericMatrix X);
RcppExport SEXP lidR_triangle_information(SEXP MSEXP, SEXP XSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type M(MSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type X(XSEXP);
    rcpp_result_gen = Rcpp::wrap(triangle_information(M, X));
    return rcpp_result_gen;
END_RCPP
}
// MorphologicalOpening
NumericVector MorphologicalOpening(NumericVector X, NumericVector Y, NumericVector Z, double resolution);
RcppExport SEXP lidR_MorphologicalOpening(SEXP XSEXP, SEXP YSEXP, SEXP ZSEXP, SEXP resolutionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type X(XSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type Y(YSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type Z(ZSEXP);
    Rcpp::traits::input_parameter< double >::type resolution(resolutionSEXP);
    rcpp_result_gen = Rcpp::wrap(MorphologicalOpening(X, Y, Z, resolution));
    return rcpp_result_gen;
END_RCPP
}
// point_in_polygon
bool point_in_polygon(NumericVector vertx, NumericVector verty, float pointx, float pointy);
RcppExport SEXP lidR_point_in_polygon(SEXP vertxSEXP, SEXP vertySEXP, SEXP pointxSEXP, SEXP pointySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type vertx(vertxSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type verty(vertySEXP);
    Rcpp::traits::input_parameter< float >::type pointx(pointxSEXP);
    Rcpp::traits::input_parameter< float >::type pointy(pointySEXP);
    rcpp_result_gen = Rcpp::wrap(point_in_polygon(vertx, verty, pointx, pointy));
    return rcpp_result_gen;
END_RCPP
}
// points_in_polygon
LogicalVector points_in_polygon(NumericVector vertx, NumericVector verty, NumericVector pointx, NumericVector pointy);
RcppExport SEXP lidR_points_in_polygon(SEXP vertxSEXP, SEXP vertySEXP, SEXP pointxSEXP, SEXP pointySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type vertx(vertxSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type verty(vertySEXP);
    Rcpp::traits::input_parameter< NumericVector >::type pointx(pointxSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type pointy(pointySEXP);
    rcpp_result_gen = Rcpp::wrap(points_in_polygon(vertx, verty, pointx, pointy));
    return rcpp_result_gen;
END_RCPP
}
// points_in_polygons
IntegerVector points_in_polygons(Rcpp::List vertx, Rcpp::List verty, NumericVector pointx, NumericVector pointy);
RcppExport SEXP lidR_points_in_polygons(SEXP vertxSEXP, SEXP vertySEXP, SEXP pointxSEXP, SEXP pointySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type vertx(vertxSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type verty(vertySEXP);
    Rcpp::traits::input_parameter< NumericVector >::type pointx(pointxSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type pointy(pointySEXP);
    rcpp_result_gen = Rcpp::wrap(points_in_polygons(vertx, verty, pointx, pointy));
    return rcpp_result_gen;
END_RCPP
}
