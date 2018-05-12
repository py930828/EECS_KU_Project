#include "PreconditionViolationException.h"
using namespace std;
PreconditionViolationException::PreconditionViolationException(const char* message):runtime_error(message)
{	
}
