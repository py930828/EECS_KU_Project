#include <stdexcept>
using namespace std;
#ifndef PRECONDITIONVIOLATIONEXCEPTION_H_
#define PRECONDITIONVIOLATIONEXCEPTION_H_
/*  
 *@pre:none
 *@post:create a inheritence of runtime_error object
 *@return:none
 */
class PreconditionViolationException:public runtime_error
{
public:
PreconditionViolationException(const char* message);
};
#endif
