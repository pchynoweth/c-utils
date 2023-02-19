#include "cutils_heap.h"

#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>


cutils_heap_t* heap = NULL;

int cmp(int const* lhs, int const* rhs) {
    return *lhs - *rhs;
}

void setup(void)
{
    heap = cutils_heap_create(sizeof(int), (cutils_cmp_t)cmp);
}

void teardown(void)
{
    cutils_heap_free(heap);
}

START_TEST(test_heap_size)
{
    ck_assert_uint_eq(cutils_heap_size(heap), 0);
    ck_assert_uint_eq(cutils_heap_is_empty(heap), 1);

    int val = 2;
    cutils_heap_push(heap, &val);

    ck_assert_uint_eq(cutils_heap_size(heap), 1);
    ck_assert_uint_eq(cutils_heap_is_empty(heap), 0);
}
END_TEST

START_TEST(test_heap_push_and_pop)
{
    int vals[] = {5,2,6,7,8,1,9,3};
    int sorted_vals[sizeof(vals) / sizeof(*vals)];

    memcpy(sorted_vals, vals, sizeof(vals));
    qsort(
        sorted_vals,
        sizeof(sorted_vals) / sizeof(*sorted_vals),
        sizeof(*sorted_vals),
        (cutils_cmp_t)cmp
    );

    for (size_t i = 0; i < sizeof(vals) / sizeof(*vals); ++i) {
        ck_assert_uint_eq(cutils_heap_size(heap), i);
        cutils_heap_push(heap, &vals[i]);
        ck_assert_uint_eq(cutils_heap_size(heap), i+1);
    }

    for (size_t i = 0; i < sizeof(vals) / sizeof(*vals); ++i) {
        int const* peek = cutils_heap_peek(heap);
        ck_assert_ptr_nonnull(peek);
        if (peek) {
            ck_assert_int_eq(*peek, sorted_vals[i]);
        }
        int const* pop = cutils_heap_pop(heap);
        ck_assert_ptr_nonnull(pop);
        if (pop) {
            ck_assert_int_eq(*pop, sorted_vals[i]);
        }
    }
}
END_TEST

Suite * heap_suite(void)
{
    Suite *s;
    TCase *tc_core;
    //TCase *tc_limits;

    s = suite_create("Heap");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_heap_size);
    tcase_add_test(tc_core, test_heap_push_and_pop);
    suite_add_tcase(s, tc_core);

    // /* Limits test case */
    //tc_limits = tcase_create("Limits");

    //tcase_add_test(tc_limits, test_money_create_neg);
    //tcase_add_test(tc_limits, test_money_create_zero);
    //suite_add_tcase(s, tc_limits);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = heap_suite();
    sr = srunner_create(s);

    srunner_set_log(sr, "test.log");
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
