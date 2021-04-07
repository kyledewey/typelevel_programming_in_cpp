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
  ParamType typedef paramType;
  ReturnType typedef returnType;
};

template <typename T1, typename T2>
struct ProductType {
  enum { debugFlag = 3 };
  T1 typedef productT1;
  T2 typedef productT2;
};

template <typename T1, typename T2>
struct SumType {
  enum { debugFlag = 4 };
  T1 typedef sumT1;
  T2 typedef sumT2;
};
// ---END DEFINITIONS FOR TYPES---

// ---BEGIN DEFINITIONS FOR AST---
template <typename N>
struct NatLiteral {
  N typedef value;
};

template <typename B>
struct BoolLiteral {
  B typedef value;
};

template <typename Name>
struct VariableExp {
  Name typedef name;
};

template <typename E1, typename E2>
struct AddExp {
  E1 typedef e1;
  E2 typedef e2;
};

template <typename E1, typename E2>
struct AndExp {
  E1 typedef e1;
  E2 typedef e2;
};

template <typename E1, typename E2>
struct EqualsExp {
  E1 typedef e1;
  E2 typedef e2;
};

template <typename X, typename E1, typename E2>
struct LetExp {
  X typedef x;
  E1 typedef e1;
  E2 typedef e2;
};

template <typename X, typename XType, typename E1, typename E2>
struct RecExp {
  X typedef x;
  XType typedef xType;
  E1 typedef e1;
  E2 typedef e2;
};

template <typename E1, typename E2, typename E3>
struct IfExp {
  E1 typedef e1;
  E2 typedef e2;
  E3 typedef e3;
};

template <typename X, typename XType, typename E>
struct LambdaExp {
  X typedef x;
  XType typedef xType;
  E typedef eType;
};

template <typename E1, typename E2>
struct CallExp {
  E1 typedef e1;
  E2 typedef e2;
};

template <typename E1, typename E2>
struct ProductExp {
  E1 typedef e1;
  E2 typedef e2;
};

template <typename E>
struct FstExp {
  E typedef e;
};

template <typename E>
struct SndExp {
  E typedef e;
};

template <typename E, typename RightType>
struct SumLeftExp {
  E typedef e;
  RightType typedef rightType;
};

template <typename LeftType, typename E>
struct SumRightExp {
  LeftType typedef leftType;
  E typedef e;
};

template <typename On, typename LeftX, typename LeftExp, typename RightX, typename RightExp>
struct MatchExp {
  On typedef on;
  LeftX typedef leftX;
  LeftExp typedef leftExp;
  RightX typedef rightX;
  RightExp typedef rightExp;
};
// ---END DEFINITIONS FOR AST---

// ---BEGIN DEFINITIONS FOR TYPECHECKER---
template <typename E, typename Map>
struct TypeOf {};

template <typename N, typename Map>
struct TypeOf<NatLiteral<N>, Map> {
  typename IsNat<N>::ok typedef nOk;
  NatType typedef result;
};

template <typename B, typename Map>
struct TypeOf<BoolLiteral<B>, Map> {
  typename IsBool<B>::ok typedef bOk;
  BoolType typedef result;
};

template <typename Name, typename Map>
struct TypeOf<VariableExp<Name>, Map> {
  typename Lookup<Map, Name>::result typedef result;
};

template <typename T1, typename T2>
struct SameType {};

template <typename T>
struct SameType<T, T> {
  True typedef ok;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<AddExp<E1, E2>, Map> {
  typename SameType<typename TypeOf<E1, Map>::result, NatType>::ok typedef e1Ok;
  typename SameType<typename TypeOf<E2, Map>::result, NatType>::ok typedef e2Ok;
  NatType typedef result;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<AndExp<E1, E2>, Map> {
  typename SameType<typename TypeOf<E1, Map>::result, BoolType>::ok typedef e1Ok;
  typename SameType<typename TypeOf<E2, Map>::result, BoolType>::ok typedef e2Ok;
  BoolType typedef result;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<EqualsExp<E1, E2>, Map> {
  typename SameType<typename TypeOf<E1, Map>::result,
                    typename TypeOf<E2, Map>::result>::ok typedef e1E2HaveSameTypes;
  BoolType typedef result;
};

// Let: put variable in scope with type of first expression, and evaluate
// second expression
template <typename X, typename E1, typename E2, typename Map>
struct TypeOf<LetExp<X, E1, E2>, Map> {
  typename TypeOf<E2,
                  NonEmptyMap<X,
                              typename TypeOf<E1, Map>::result,
                              Map> >::result typedef result;
};

// Rec: make sure E1 is of the provided type.
// Put E1's type in scope while typechecking E1.
template <typename X, typename XType, typename E1, typename E2, typename Map>
struct TypeOf<RecExp<X, XType, E1, E2>, Map> {
  typename SameType<typename TypeOf<E1, NonEmptyMap<X, XType, Map> >::result, XType>::ok typedef e1TypeOk;
  typename TypeOf<E2,
                  NonEmptyMap<X, XType, Map> >::result typedef result;
};

// if: e1 should be a boolean
// e2 and e3 should have the same types, and the return type is the same as these
template <typename E1, typename E2, typename E3, typename Map>
struct TypeOf<IfExp<E1, E2, E3>, Map> {
  typename SameType<typename TypeOf<E1, Map>::result, BoolType>::ok typedef e1TypeOk;
  typename SameType<typename TypeOf<E2, Map>::result,
                    typename TypeOf<E3, Map>::result>::ok typedef e2E3HaveSameTypes;
  typename TypeOf<E2, Map>::result typedef result;
};

// lambda: x is put into scope with declared type
template <typename X, typename XType, typename E, typename Map>
struct TypeOf<LambdaExp<X, XType, E>, Map> {
  LambdaType<XType,
             typename TypeOf<E, NonEmptyMap<X, XType, Map> >::result> typedef result;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<CallExp<E1, E2>, Map> {
  typename SameType<typename TypeOf<E1, Map>::result::paramType,
                    typename TypeOf<E2, Map>::result>::ok typedef isLambdaWithOkParamType;
  typename TypeOf<E1, Map>::result::returnType typedef result;
};

template <typename E1, typename E2, typename Map>
struct TypeOf<ProductExp<E1, E2>, Map> {
  ProductType<typename TypeOf<E1, Map>::result,
              typename TypeOf<E2, Map>::result> typedef result;
};

template <typename E, typename Map>
struct TypeOf<FstExp<E>, Map> {
  typename TypeOf<E, Map>::result::productT1 typedef result;
};

template <typename E, typename Map>
struct TypeOf<SndExp<E>, Map> {
  typename TypeOf<E, Map>::result::productT2 typedef result;
};

template <typename E, typename RightType, typename Map>
struct TypeOf<SumLeftExp<E, RightType>, Map> {
  SumType<typename TypeOf<E, Map>::result,
          RightType> typedef result;
};

template <typename LeftType, typename E, typename Map>
struct TypeOf<SumRightExp<LeftType, E>, Map> {
  SumType<LeftType,
          typename TypeOf<E, Map>::result> typedef result;
};

// ---END DEFINITIONS FOR TYPECHECKER---

#endif
