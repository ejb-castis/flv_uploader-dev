
void ptr() {

  int num = 77;
  int * pointer_to_int = &num;
  const int * pointer_to_const_int = &num;
  int * const const_pointer_to_int = &num;
  int * * const const_pointer_to_pointer_to_int = &pointer_to_int;
  int * * const * pointer_to_const_pointer_to_pointer_to_int = &const_pointer_to_pointer_to_int;

  const int* * pointer_to_pointer_to_const_int = &pointer_to_const_int;
  int * * const * * pointer_to_pointer_to_const_pointer_to_pointer_to_int = &pointer_to_const_pointer_to_pointer_to_int;

  int const * const * const * pointer_to_cosnt_pointer_to_const_pointer_to_const_int;
}