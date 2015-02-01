#include <tet_api.h>
#include <bundle.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_ApplicationFW_bundle_import_from_argv_func_01(void);
static void utc_ApplicationFW_bundle_import_from_argv_func_02(void);

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

struct tet_testlist tet_testlist[] = {
	{ utc_ApplicationFW_bundle_import_from_argv_func_01, POSITIVE_TC_IDX },
	{ utc_ApplicationFW_bundle_import_from_argv_func_02, NEGATIVE_TC_IDX },
	{ NULL, 0 }
};

static void startup(void)
{
}

static void cleanup(void)
{
}

/**
 * @brief Positive test case of bundle_import_from_argv()
 */
static void utc_ApplicationFW_bundle_import_from_argv_func_01(void)
{
	bundle *b = NULL;
	int argc = 0;
	char **argv = NULL;
	int r = 0;
        bundle *b_new = NULL;
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

        argc = bundle_export_to_argv(b,&argv);
	if (argc < 0) {
                tet_result(TET_UNINITIATED);
		return;
	}

	b_new = bundle_import_from_argv(argc, argv);
	if (b_new == NULL) {
		tet_infoline("bundle_import_from_argv() failed in positive test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}

/**
 * @brief Negative test case of bundle_import_from_argv()
 */
static void utc_ApplicationFW_bundle_import_from_argv_func_02(void)
{
	int r = 0;
	bundle *b = NULL;
	int argc = 3;
	b = bundle_import_from_argv(argc, NULL);
	if (b != NULL) {
		tet_infoline("bundle_import_from_argv() failed in negative test case");
		tet_result(TET_FAIL);
		return;
	}
	tet_result(TET_PASS);
}
