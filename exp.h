#ifndef EXP_H
#define EXP_H

// C++-based definition of https://github.com/csun-tavlab/scala_typelevel_experimentation/blob/master/exp.scala
// A type-level typechecker for a simple functional programming language.

#include "peano.h"
#include "map.h"

// ---BEGIN DEFINITIONS FOR TYPES---
struct BoolType {
  enum { debugFlag = 0 };
};
struct NatType {
  enum { debugFlag = 1 };
};

template <typename ParamType, typename ReturnType>
struct LambdaType {
  enum { debugFlag = 2 };
  using paramType = ParamType;
  using returnType = ReturnType;
};

template <typename T1, typename T2>
struct ProductType {
  enum { debugFlag = 3 };
  using productT1 = T1;
  using productT2 = T2;
};

template <typename T1, typename T2>
struct SumType {
  enum { debugFlag = 4 };
  using sumT1 = T1;
  using sumT2 = T2;
};
// ---END DEFINITIONS FOR TYPES---

// ---BEGIN DEFINITIONS FOR AST---
template <typename N>
struct NatLiteral {
  using value = N;
};

template <typename B>
struct BoolLiteral {
  using value = B;
};

template <typename Name>
struct VariableExp {
  using name = Name;
};

template <typename E1, typename E2>
struct AddExp {
  using e1 = E1;
  using e2 = E2;
};

template <typename E1, typename E2>
struct AndExp {
  using e1 = E1;
  using e2 = E2;
};

template <typename E1, typename E2>
struct EqualsExp {
  using e1 = E1;
  using e2 = E2;
};

template <typename X, typename E1, typename E2>
struct LetExp {
  using x = X;
  using e1 = E1;
  using e2 = E2;
};

template <typename X, typename XType, typename E1, typename E2>
struct RecExp {
  using x = X;
  using xType = XType;
  using e1 = E1;
  using e2 = E2;
};

template <typename E1, typename E2, typename E3>
struct IfExp {
  using e1 = E1;
  using e2 = E2;
  using e3 = E3;
};

template <typename X, typename XType, typename E>
struct LambdaExp {
  using x = X;
  using xType = XType;
  using eType = E;
};

template <typename E1, typename E2>
struct CallExp {
  using e1 = E1;
  using e2 = E2;
};

template <typename E1, typename E2>
struct ProductExp {
  using e1 = E1;
  using e2 = E2;
};

template <typename E>
struct FstExp {
  using e = E;
};

template <typename E>
struct SndExp {
  using e = E;
};

template <typename E, typename RightType>
struct SumLeftExp {
  using e = E;
  using rightType = RightType;
};

template <typename LeftType, typename E>
struct SumRightExp {
  using leftType = LeftType;
  using e = E;
};

template <typename On, typename LeftX, typename LeftExp, typename RightX, typename RightExp>
struct MatchExp {
  using on = On;
  using leftX = LeftX;
  using leftExp = LeftExp;
  using rightX = RightX;
  using rightExp = RightExp;
};
// ---END DEFINITIONS FOR AST---

// ---BEGIN DEFINITIONS FOR TYPECHECKER---
template <typename E, typename Map>
struct TypeOf {};

template <typename N, typename Map>
struct TypeOf<NatLiteral<N>, Map> {
  using nOk = typename IsNat<N>::ok;
  using result = NatType;
};

template <typename B, typename Map>
struct TypeOf<BoolLiteral<B>, Map> {
  using bOk = typename IsBool<B>::ok;
  using result = BoolType;
};

template <typename Name, typename Map>
struct TypeOf<VariableExp<Name>, Map> {
  using result = typename Lookup<Map, Name>::result;
};

template <typename T1, typename T2>
struct SameType {};

template <typename T>
struct SameType<T, T> {
  using ok = True;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<AddExp<E1, E2>, Map> {
  using e1Ok = typename SameType<typename TypeOf<E1, Map>::result, NatType>::ok;
  using e2Ok = typename SameType<typename TypeOf<E2, Map>::result, NatType>::ok;
  using result = NatType;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<AndExp<E1, E2>, Map> {
  using e1Ok = typename SameType<typename TypeOf<E1, Map>::result, BoolType>::ok;
  using e2Ok = typename SameType<typename TypeOf<E2, Map>::result, BoolType>::ok;
  using result = BoolType;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<EqualsExp<E1, E2>, Map> {
  using e1E2HaveSameTypes = typename SameType<typename TypeOf<E1, Map>::result,
                                              typename TypeOf<E2, Map>::result>::ok;
  using result = BoolType;
};

// Let: put variable in scope with type of first expression, and evaluate
// second expression
template <typename X, typename E1, typename E2, typename Map>
struct TypeOf<LetExp<X, E1, E2>, Map> {
  using result = typename TypeOf<E2,
                                 NonEmptyMap<X,
                                             typename TypeOf<E1, Map>::result,
                                             Map> >::result;
};

// Rec: make sure E1 is of the provided type.
// Put E1's type in scope while typechecking E1.
template <typename X, typename XType, typename E1, typename E2, typename Map>
struct TypeOf<RecExp<X, XType, E1, E2>, Map> {
  using e1TypeOk = typename SameType<typename TypeOf<E1, NonEmptyMap<X, XType, Map> >::result,
                                     XType>::ok;
  using result = typename TypeOf<E2,
                                 NonEmptyMap<X, XType, Map> >::result;
};

// if: e1 should be a boolean
// e2 and e3 should have the same types, and the return type is the same as these
template <typename E1, typename E2, typename E3, typename Map>
struct TypeOf<IfExp<E1, E2, E3>, Map> {
  using e1TypeOk = typename SameType<typename TypeOf<E1, Map>::result, BoolType>::ok;
  using e2E3HaveSameTypes = typename SameType<typename TypeOf<E2, Map>::result,
                                              typename TypeOf<E3, Map>::result>::ok;
  using result = typename TypeOf<E2, Map>::result;
};

// lambda: x is put into scope with declared type
template <typename X, typename XType, typename E, typename Map>
struct TypeOf<LambdaExp<X, XType, E>, Map> {
  using result = LambdaType<XType,
                            typename TypeOf<E, NonEmptyMap<X, XType, Map> >::result>;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<CallExp<E1, E2>, Map> {
  using isLambdaWithOkParamType = typename SameType<typename TypeOf<E1, Map>::result::paramType,
                                                    typename TypeOf<E2, Map>::result>::ok;
  using result = typename TypeOf<E1, Map>::result::returnType;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<ProductExp<E1, E2>, Map> {
  using result = ProductType<typename TypeOf<E1, Map>::result,
                             typename TypeOf<E2, Map>::result>;
};

template <typename E, typename Map>
struct TypeOf<FstExp<E>, Map> {
  using result = typename TypeOf<E, Map>::result::productT1;
};

template <typename E, typename Map>
struct TypeOf<SndExp<E>, Map> {
  using result = typename TypeOf<E, Map>::result::productT2;
};

template <typename E, typename RightType, typename Map>
struct TypeOf<SumLeftExp<E, RightType>, Map> {
  using result = SumType<typename TypeOf<E, Map>::result,
                         RightType>;
};

template <typename LeftType, typename E, typename Map>
struct TypeOf<SumRightExp<LeftType, E>, Map> {
  using result = SumType<LeftType,
                         typename TypeOf<E, Map>::result>;
};

// types of the branches need to be the same
// return type is whatever either branch is (mirrors if)
template <typename On, typename LeftX, typename LeftExp, typename RightX, typename RightExp, typename Map>
struct TypeOf<MatchExp<On, LeftX, LeftExp, RightX, RightExp>, Map> {
  // get the sum type
  // typename TypeOf<On, Map>::result

  // get the type of the left branch
  // typename TypeOf<LeftExp,
  //                 NonEmptyMap<LeftX, 
  //                             typename TypeOf<On, Map>::result::sumT1,
  //                             Map> >::result

  // get the type of the right branch
  // typename TypeOf<RightExp,
  //                 NonEmptyMap<RightX, 
  //                             typename TypeOf<On, Map>::result::sumT2,
  //                             Map> >::result

  using branchesHaveSameType =
    typename SameType<typename TypeOf<LeftExp,
                                      NonEmptyMap<LeftX,
                                                  typename TypeOf<On, Map>::result::sumT1,
                                                  Map> >::result,
                      typename TypeOf<RightExp,
                                      NonEmptyMap<RightX,
                                                  typename TypeOf<On, Map>::result::sumT2,
                                                  Map> >::result>::ok;
  using result = typename TypeOf<LeftExp,
                                 NonEmptyMap<LeftX,
                                             typename TypeOf<On, Map>::result::sumT1,
                                             Map> >::result;
};

// ---END DEFINITIONS FOR TYPECHECKER---

#endif
