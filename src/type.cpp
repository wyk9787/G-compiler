#include <type.hpp>

void type_error(std::string expression, std::string expect, std::string actual) {
  std::cerr << "In " << expression << std::endl;
  std::cerr << "Expecting type " << expect << ", receiving type " << actual << std::endl;
  exit(1);
}

bool operator==(const Typ &first, const Typ &second){
  return first.eq(second);
}

bool operator!=(const Typ &first, const Typ &second){
  return !first.eq(second);
}

//********************************TInt Implementaion****************************//

TInt::TInt(){}

std::string TInt::get_type() {
  return "Int";
}

bool TInt::eq(const Typ& other) const {
  const TInt *res = dynamic_cast<const TInt*>(&other);
  return res != nullptr;
}

//********************************TFloat Implementaion****************************//

TFloat::TFloat(){}

std::string TFloat::get_type() {
  return "Float";
}

bool TFloat::eq(const Typ& other) const {
  const TFloat *res = dynamic_cast<const TFloat*>(&other);
  return res != nullptr;
}

//********************************TBool Implementaion****************************//

TBool::TBool(){}

bool TBool::eq(const Typ& other) const {
  const TBool *res = dynamic_cast<const TBool*>(&other);
  return res != nullptr;
}

std::string TBool::get_type() {
  return "Boolean";
}

//********************************TUnit Implementaion****************************//

TUnit::TUnit(){}

std::string TUnit::get_type() {
  return "unit";
}

bool TUnit::eq(const Typ& other) const {
  const TUnit *res = dynamic_cast<const TUnit*>(&other);
  return res != nullptr;
}

//********************************TFunc Implementaion****************************//

TFunc::TFunc(Shared_Typ _t1, Shared_Typ _t2) : t1(_t1), t2(_t2) {};

bool TFunc::eq(const Typ& other) const {
  const TFunc *res = dynamic_cast<const TFunc*>(&other);
  return res != nullptr && *t1.get() == *const_cast<Typ&>(other).get_first_subtype().get() && *t2.get() == *const_cast<Typ&>(other).get_second_subtype().get();
}

std::string TFunc::get_type() {
  return t1->get_type() + " -> " + t2->get_type();
}

Shared_Typ TFunc::get_first_subtype() {
  return t1;
}

Shared_Typ TFunc::get_second_subtype() {
  return t2;
}
