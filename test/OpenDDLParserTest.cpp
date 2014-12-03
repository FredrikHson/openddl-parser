/*-----------------------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Kim Kulling

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------*/
#include "gtest/gtest.h"

#include <openddlparser\OpenDDLParser.h>

BEGIN_ODDLPARSER_NS

class OpenDDLParserTest : public testing::Test {
protected:
};

TEST_F(OpenDDLParserTest, isUpperCaseTest) {
    char val = 'a';
    EXPECT_TRUE(isLowerCase<char>(val));
    val = 'c';
    EXPECT_TRUE(isLowerCase<char>(val));
    val = 'z';
    EXPECT_TRUE(isLowerCase<char>(val));
    val = 'A';
    EXPECT_FALSE(isLowerCase<char>(val));
    val = '0';
    EXPECT_FALSE(isLowerCase<char>(val));
}

TEST_F(OpenDDLParserTest, isLowerCaseTest) {
    char val = 'A';
    EXPECT_TRUE(isUpperCase<char>(val));
    val = 'C';
    EXPECT_TRUE(isUpperCase<char>(val));
    val = 'Z';
    EXPECT_TRUE(isUpperCase<char>(val));
    val = 'a';
    EXPECT_FALSE(isUpperCase<char>(val));
    val = '0';
    EXPECT_FALSE(isUpperCase<char>(val));
}

TEST_F(OpenDDLParserTest, isNumericTest) {
    char val1 = '0';
    EXPECT_TRUE( isNumeric<char>(val1) );
    char val2 = '9';
    EXPECT_TRUE(isNumeric<char>(val2));
    char val3 = '4';
    EXPECT_TRUE(isNumeric<char>(val3));
    char not = 'a';
    EXPECT_FALSE(isNumeric<char>(not));
}

TEST_F( OpenDDLParserTest, isSeparatorTest ) {
    char val;
    val = ' ';
    EXPECT_TRUE( isSeparator( val ) );
    val = '\n';
    EXPECT_TRUE( isSeparator( val ) );
    val = '\t';
    EXPECT_TRUE( isSeparator( val ) );
    val = '1';
    EXPECT_FALSE( isSeparator( val ) );
    val = 'a';
    EXPECT_FALSE( isSeparator( val ) );
    val = 'Z';
    EXPECT_FALSE( isSeparator( val ) );
}

TEST_F( OpenDDLParserTest, createTest ) {
    bool success( true );
    try {
        OpenDDLParser myParser;
        EXPECT_EQ( nullptr, myParser.getRoot() );
    } catch( ... ) {
        success = false;
    }
    EXPECT_TRUE( success );
}

TEST_F( OpenDDLParserTest, parseIdTest ) {
    size_t offset( 0 );
    const char name1[] = "testname";
    Identifier *id = OpenDDLParser::parseIdentifier( name1, strlen( name1 ), offset );
    EXPECT_TRUE( id != nullptr );
}

TEST_F( OpenDDLParserTest, parseNameTest ) {
    size_t offset( 0 );
    const char name1[] = "$testname";
    Name *name = OpenDDLParser::parseName( name1, strlen( name1 ), offset );
    EXPECT_TRUE( name != nullptr );
}

TEST_F( OpenDDLParserTest, parsePrimitiveDataTypeTest ) {
    PrimData *data( nullptr );

    size_t offset( 0 );
    data = OpenDDLParser::parsePrimitiveDataType( nullptr, 1, offset );
    EXPECT_EQ( nullptr, data );

    const char token1[] = "float";
    const size_t len( strlen( token1 ) );
    data = OpenDDLParser::parsePrimitiveDataType( token1, len, offset );
    EXPECT_NE( nullptr, data );

    const char invalidToken[] = "foat";
    const size_t len1( strlen( invalidToken ) );

    data = OpenDDLParser::parsePrimitiveDataType( invalidToken, len1, offset );
    EXPECT_EQ( nullptr, data );
}
 
TEST_F( OpenDDLParserTest, parsePrimitiveDataTypeWithArrayTest ) {
    size_t offset( 0 );
    PrimData *data( nullptr );
    const char token[] = "float[3]";
    const size_t len( strlen( token ) );
    data = OpenDDLParser::parsePrimitiveDataType( token, len, offset );
    ASSERT_NE( nullptr, data );
    EXPECT_EQ( ddl_float, data->m_type );
    EXPECT_EQ( 12, data->m_size );
    EXPECT_NE( nullptr, data->m_data );
}

TEST_F( OpenDDLParserTest, parsePrimitiveDataTypeWithInvalidArrayTest ) {
    size_t offset( 0 );
    PrimData *data( nullptr );
    const char token1[] = "float[3";
    const size_t len1( strlen( token1 ) );
    data = OpenDDLParser::parsePrimitiveDataType( token1, len1, offset );
    EXPECT_EQ( nullptr, data );
}

END_ODDLPARSER_NS
