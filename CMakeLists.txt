CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(ssget CXX)

ENABLE_TESTING()

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

SET(POCO_ROOT $ENV{POCO_ROOT})
SET(POCO_INCLUDE_DIR "${POCO_ROOT}/include")
SET(POCO_LIB_DIR "${POCO_ROOT}/lib")
INCLUDE_DIRECTORIES(${POCO_INCLUDE_DIR})
LINK_DIRECTORIES(${POCO_LIB_DIR})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_EXECUTABLE(ssget main.cpp WebDownloader.cpp JsonParser.cpp)

TARGET_LINK_LIBRARIES(ssget PocoNetSSLWin$<$<CONFIG:Debug>:d>
                            PocoCrypto$<$<CONFIG:Debug>:d>
                            PocoFoundation$<$<CONFIG:Debug>:d>
                            PocoUtil$<$<CONFIG:Debug>:d>
                            PocoNet$<$<CONFIG:Debug>:d>)

FUNCTION(ADD_SSGET_TEST TEST_NAME)
    SET(ARGUMENTS ${ARGN})
    LIST(POP_BACK ARGUMENTS EXPECTED_OUTPUT)
    ADD_TEST(
        NAME ${TEST_NAME}
        COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ssget ${ARGUMENTS}
    )
    SET_TESTS_PROPERTIES(${TEST_NAME} PROPERTIES PASS_REGULAR_EXPRESSION ${EXPECTED_OUTPUT})
ENDFUNCTION()

ADD_SSGET_TEST(UnknownArg "unknown" "Unknown argument\nssget")
ADD_SSGET_TEST(Fetch fetch "Missing key to fetch")
ADD_SSGET_TEST(FetchInvalid fetch invalid_key "Invalid key")
ADD_SSGET_TEST(FetchContentId fetch content_id "content_id com.ubuntu.cloud:released:download")
ADD_SSGET_TEST(FetchProducts fetch products "Products:\n- com.ubuntu.cloud:server:10.04:amd64")
ADD_SSGET_TEST(FetchSupportedProducts fetch supported_products "Supported products:\n- com.ubuntu.cloud:server:20.04:amd64")
ADD_SSGET_TEST(FetchCurrentLTS fetch current_lts "Latest LTS version: 24.04 LTS")
ADD_SSGET_TEST(FetchSHA2410 fetch sha256 24.10 amd64 20241009 "SHA256: b1b653186a01eb75bacb6bf15eac494d888f61f7adc3084e3d94fd117ddc82f5")
ADD_SSGET_TEST(FetchSHA2204 fetch sha256 22.04 amd64 20220902 "SHA256: c777670007cc5f132417b9e0bc01367ccfc2a989951ffa225bb1952917c3aa81")
ADD_SSGET_TEST(FetchSHA1104 fetch sha256 11.04 i386 20121028 "SHA256: 39c19059bbe3eff7ef81a609e21445a173ef1ce7fa45d7e16b8d7e3bbabb0c41")
ADD_SSGET_TEST(FetchSHAIncomplete fetch sha256 "One or more arguments are missing in order to fetch sha256")
