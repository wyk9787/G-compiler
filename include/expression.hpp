#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "token.hpp"
#include "type.hpp"
#include <memory>
#include <iostream>

class Exp;
class EOperator;
class EComp;
class ELit;
class EBool;
class EVar;
class EFunc;
class EIf;
class ELet;
class EApp;

/******************************************************************************
                               Exp Header
*******************************************************************************/

class Exp {
public:
  virtual Shared_Exp step() = 0;
  virtual Shared_Exp substitute(std::string var, Shared_Exp t) = 0;
  virtual std::string string_of_exp() = 0;
  virtual Shared_Typ typecheck(context_t context) = 0;

  virtual bool is_value() { return false; }
  virtual bool is_bool() { return false; }
  virtual bool is_int() { return false; }
  virtual bool is_float() {return false; }
  virtual bool is_unit() {return false; }
  virtual bool is_NaN() { return false; }
  virtual bool is_var() { return false; }
  virtual bool is_func() { return false; }


  virtual bool get_bool() {
    std::cerr << "Debug: Expecting a boolean!\n";
    exit(1);
  }
  virtual int get_int() {
    std::cerr << "Debug: Expecting an integer!\n";
    exit(1);
  }
  virtual std::string get_NaN() {
    std::cerr << "Debug: Expecting an integer!\n";
    exit(1);
  }
  virtual double get_float() {
    std::cerr << "Debug: Expecting a float!\n";
    exit(1);
  }
  virtual std::string get_var() {
    std::cerr << "Debug: Expecting a variable!\n";
    exit(1);
  }
  virtual std::shared_ptr<EFunc> get_func() {
    std::cerr << "Debug: Expecting a boolean!\n";
    exit(1);
  }
  virtual ~Exp(){};
};

/******************************************************************************
                               EOperator Header
*******************************************************************************/

class EOperator : public Exp {
private:
  TokenKind id;
  Shared_Exp e1, e2;
  Shared_Exp evaluate_num(Shared_Exp e1, Shared_Exp e2, bool is_int);

public:
  EOperator(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp t);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);
};

/******************************************************************************
                               EComp Header
*******************************************************************************/

class EComp : public Exp {
private:
  TokenKind id;
  Shared_Exp e1, e2;
  Shared_Exp evaluate_bool(Shared_Exp e1, Shared_Exp e2);

public:
  EComp(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp t);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);
};


/******************************************************************************
                               ELit Header
*******************************************************************************/

class ELit : public Exp {
private:
  bool _is_int;
  bool _is_NaN;
  int int_data;
  double float_data;
public:
  ELit(bool __is_int, int _int_data, double _float_data, bool __is_NaN);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp e);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);

  bool is_value();
  bool is_int();
  int get_int();
  bool is_float();
  double get_float();
  bool is_NaN();
  std::string get_NaN();
};

/******************************************************************************
                               EBool Header
*******************************************************************************/

class EBool : public Exp {
private:
  bool data;
public:
  EBool(bool _data);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp e);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);

  bool is_value();
  bool is_bool();
  bool get_bool();
};

/******************************************************************************
                               EVar Header
*******************************************************************************/

class EVar : public Exp {
private:
  std::string data;

public:
  EVar(std::string _data);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp e);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);

  bool is_value();
  bool is_var();
  std::string get_var();
};

/******************************************************************************
                               EFunc Header
*******************************************************************************/

class EFunc : public Exp {
private:
  std::string param;
  Shared_Typ t1;
  Shared_Typ t2;
  Shared_Exp e;
  bool is_rec;
  std::string id;

public:
  EFunc(std::string _param, Shared_Typ _t1, Shared_Typ _t2, Shared_Exp _e, bool _is_rec, std::string _id);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp e);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);

  bool is_value();
  bool is_func();
  std::shared_ptr<EFunc> get_func();
  Shared_Exp get_function_body();
  std::string get_param();
  bool get_is_rec();
  std::string get_id();
};

/******************************************************************************
                               EUnit Header
*******************************************************************************/

class EUnit : public Exp {
private:

public:
  EUnit();
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp e);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);

  bool is_value();
  bool is_unit();
};

/******************************************************************************
                               EIf Header
*******************************************************************************/

class EIf : public Exp {
private:
  Shared_Exp e1, e2, e3;

public:
  EIf(Shared_Exp _e1, Shared_Exp _e2,
      Shared_Exp _e3);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp t);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);
};

/******************************************************************************
                               ELet Header
*******************************************************************************/

class ELet : public Exp {
private:
  std::string var;
  Shared_Typ t;
  Shared_Exp e1, e2;

public:
  ELet(std::string _var, Shared_Typ _t, Shared_Exp _e1, Shared_Exp _e2);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp t);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);
};

/******************************************************************************
                               EApp Header
*******************************************************************************/

class EApp : public Exp {
private:
  Shared_Exp function;
  Shared_Exp e;


public:
  EApp(Shared_Exp _function, Shared_Exp _e);
  Shared_Exp step();
  Shared_Exp substitute(std::string var, Shared_Exp t);
  std::string string_of_exp();
  Shared_Typ typecheck(context_t context);
};

/******************************************************************************
                               Helper
*******************************************************************************/

Shared_Exp evaluate(Shared_Exp exp, bool print_step);

#endif
