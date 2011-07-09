#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <string>
#include <cstdlib>
#include <ostream>
#include <sstream>
#ifdef WIN32
#    include <Windows.h>
#endif

//! namespace for the test framework
namespace TF
{

//! An exception class representing a test assertion failure.
class Failure
{
public:

    //! Constructs an exception with the given details.
    Failure( const char* message, const char* file, unsigned int line )
        : m_message( message )
        , m_file( file )
        , m_line( line )
    {
    }

    //! Returns a description of the test that failed.
    const std::string& GetMessage() const  { return m_message; }

    //! Returns the name of the source file where the failed test resides.
    const std::string& GetFile() const     { return m_file; }

    //! Returns the source line number where the failed test resides.
    unsigned int GetLine() const           { return m_line; }

private:

    std::string m_message;
    std::string m_file;
    unsigned int m_line;
};

//! Throws a Failure exception if the given condition is false.
inline void Assert( bool condition, const char* message, const char* file
               , unsigned int line )
{
    if( !condition )
    {
        throw Failure( message, file, line );
    }
}

//! Helper structure for defining named test functions
struct TestFn
{
    //! the name of the test function
    const char* name;
    //! test function pointer
    void (*fptr)();
};

//! Helper function to log some output while running the tests
inline void Log( std::ostream& os, const std::string& str )
{
    os << str;
#ifdef WIN32
    ::OutputDebugString( str.c_str() );
#endif
}

//! Runs a sequence of tests

//! \returns EXIT_SUCCESS if the list of tests was non-empty and there were no
//!          test failures, EXIT_FAILURE otherwise.
//! \param fnarray an array of TestFn structs terminated by a final entry whose
//!        fptr member is NULL
//! \param log an output stream for writing test output
inline int RunTests( TestFn fnarray[], std::ostream& log )
{
    int fail = 0, count = 0;
    for ( TestFn* p = fnarray; p->fptr != NULL; ++p )
    {
        try
        {
            ++count;
            (*p->fptr)();
        }
        catch( const Failure& tf )
        {
            std::ostringstream failure;
#ifdef WIN32
            failure << tf.GetFile() << '(' << tf.GetLine() << ") : error TST0001: Test "
#else
            failure << tf.GetFile() << ':' << tf.GetLine() << ": Test "
#endif
                << p->name << " failed. ( " << tf.GetMessage() << " )\n";

            Log( log, failure.str() );
            ++fail;
        }
        catch( ... )
        {
            std::ostringstream failure;
#ifdef WIN32
            failure << __FILE__ << '(' << __LINE__ << ") : error TST0002: Test "
#else
            failure << __FILE__ << ':' << __LINE__ << ": Test "
#endif
                << p->name << " failed.  ( An unexpected exception was thrown. )\n";

            Log( log, failure.str() );
            ++fail;
        }
    }
    std::ostringstream result;
    result << count - fail << " out of " << count << " tests passed. " << fail << " failure" << ( fail == 1 ? "" : "s" ) << ".\n";
    Log( log, result.str() );
    return count == 0 || fail != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

} // namespace Test

//! Begins the declaration of a block of tests.
#define IG_BEGIN_TESTS namespace { TF::TestFn tests[] = {

//! Defines a test function.

//! The test function must have a definition or a prototype in scope at the
//! point at which this macro is used.
#define IG_TEST_ENTRY( t ) { #t, t },

//! Ends the declaration of a block of tests.
#define IG_END_TESTS { NULL, NULL } }; }

//! Defines a default main function for a test executable.
#define IG_TEST_MAIN int main() { return TF::RunTests( tests, std::cout ); }

//! Calls the TF::Assert function with the given condition, a
//! stringized version of the condition for a description and appropriate
//! file and line numbers.
#define IG_ASSERT( x ) TF::Assert( x, #x, __FILE__, __LINE__ )

//! Calls the TF::Assert function with the given condition, a
//! supplied description and appropriate file and line numbers.
#define IG_ASSERT_DESC( x, d ) TF::Assert( x, d, __FILE__, __LINE__ )

//! Calls the TF::Assert function with false if the given expression
//! doesn't cause an exception (other than a Failure) that can be caught
//! by a catch block of the form "catch( const except &)" for the given macro
//! parameter except.
#define IG_ASSERT_THROWS( x, except ) try { x;\
    TF::Assert( false, "Exception " #except " expected."\
        , __FILE__, __LINE__ ); } catch( const except & ) {}

#endif//TESTFRAMEWORK_H
