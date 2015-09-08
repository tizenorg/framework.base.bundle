#include <tet_api.h>
#include <bundle.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_ApplicationFW_bundle_export_to_argv_func_01(void);
static void utc_ApplicationFW_bundle_export_to_argv_func_02(void);
static void utc_ApplicationFW_bundle_export_to_argv_func_03(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_ApplicationFW_bundle_export_to_argv_func_01, POSITIVE_TC_IDX },
	{ utc_ApplicationFW_bundle_export_to_argv_func_02, NEGATIVE_TC_IDX },
	{ utc_ApplicationFW_bundle_export_to_argv_func_03, NEGATIVE_TC_IDX },
	{ NULL, 0 }
};

static void startup(void)
{
}

static void cleanup(void)
{
}

/**
 * @brief Positive test case of bundle_export_to_argv()
 */
static void utc_ApplicationFW_bundle_export_to_argv_func_01(void)
{
	int r = 0;
        bundle *b = NULL;
        char **argv1 = NULL;

        b = bundle_create();
        if(!b) {
                tet_result(TET_UNINITIATED);
                return;
        }

        r = bundle_add(b, "k1", "val1");
        if(r != 0) {
                tet_result(TET_UNINITIATED);
                return;
        }

        r = bundle_add(b, "k2", "val2");
        if(r != 0) {
                tet_result(TET_UNINITIATED);
                return;
        }

        r = bundle_export_to_argv(b,&argv1);
	if (r < 0) {
		tet_infoline("bundle_export_to_argv() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of bundle_export_to_argv()
 */
static void utc_ApplicationFW_bundle_export_to_argv_func_02(void)
{
	int r = 0;
        bundle *b = NULL;

        b = bundle_create();
        if(!b) {
                tet_result(TET_UNINITIATED);
                return;
        }

        r = bundle_add(b, "k1", "val1");
        if(r != 0) {
                tet_result(TET_UNINITIATED);
                return;
        }

        r = bundle_add(b, "k2", "val2");
        if(r != 0) {
                tet_result(TET_UNINITIATED);
                return;
        }

        r = bundle_export_to_argv(b,NULL);
	if (r != -1) {
		tet_infoline("bundle_export_to_argv() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of  bundle_export_to_argv()
 */
static void utc_ApplicationFW_bundle_export_to_argv_func_03(void)
{
	int r = 0;
        char **argv1 = NULL;

	r = bundle_export_to_argv(NULL, &argv1);
	if (r != -1) {
		tet_infoline("bundle_export_to_argv() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}
