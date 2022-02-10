/**
 * @file
 * @brief Tests implementation
 * @defgroup cred_storage_test
 * @{
 */

#include "unity.h"
#include "cred_storage.c"
#include "Mockfs.h"

#define USERNAME "Admin"
#define PASSWORD "very_strong_password"

void setUp(void)
{
  g_credentials.username[0] = '\0';
  g_credentials.password[0] = '\0';
}

void tearDown(void)
{

}

void test_CredStorageTest_store(void)
{
  credentials_t credentials = { 0 };
  strcpy(credentials.username, USERNAME);
  strcpy(credentials.password, PASSWORD);
  char* expectedFileData = USERNAME"\r\n"PASSWORD;
  fs_write_string_ExpectAndReturn(CREDENTIALS_FILENAME, expectedFileData, FS_RET_OK);
  cred_storage_ret_values res = cred_storage_save_credentials(&credentials);
  TEST_ASSERT_EQUAL_INT(CRED_ST_RET_OK, res);
  TEST_ASSERT_EQUAL_MEMORY(&credentials, &g_credentials, sizeof(credentials_t));
}

void test_CredStorageTest_store_fs_fail(void)
{
  credentials_t credentials = { 0 };
  strcpy(credentials.username, USERNAME);
  strcpy(credentials.password, PASSWORD);
  char* expectedFileData = USERNAME"\r\n"PASSWORD;
  fs_write_string_ExpectAndReturn(CREDENTIALS_FILENAME, expectedFileData, FS_RET_ERR);
  cred_storage_ret_values res = cred_storage_save_credentials(&credentials);
  TEST_ASSERT_EQUAL_INT(CRED_ST_RET_ERR, res);
  TEST_ASSERT_EQUAL(0, strlen(g_credentials.username));
  TEST_ASSERT_EQUAL(0, strlen(g_credentials.password));
}

/** @} */