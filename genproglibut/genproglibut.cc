#include "TestFramework.h"
#include "genproglib.h"
#include <iostream>

namespace
{

void Test()
{
    IG_ASSERT( genproglib::TestFunc() == 42 );
}

}

IG_BEGIN_TESTS
IG_TEST_ENTRY( Test )
IG_END_TESTS

IG_TEST_MAIN
