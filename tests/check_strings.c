/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2015 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include "../src/squareball.h"


static void
test_strdup(void **state)
{
    char *str = sb_strdup("bola");
    assert_string_equal(str, "bola");
    free(str);
    str = sb_strdup(NULL);
    assert_null(str);
}


static void
test_strndup(void **state)
{
    char *str = sb_strndup("bolaguda", 4);
    assert_string_equal(str, "bola");
    free(str);
    str = sb_strndup("bolaguda", 30);
    assert_string_equal(str, "bolaguda");
    free(str);
    str = sb_strndup("bolaguda", 8);
    assert_string_equal(str, "bolaguda");
    free(str);
    str = sb_strdup(NULL);
    assert_null(str);
}


static void
test_strdup_printf(void **state)
{
    char *str = sb_strdup_printf("bola");
    assert_string_equal(str, "bola");
    free(str);
    str = sb_strdup_printf("bola, %s", "guda");
    assert_string_equal(str, "bola, guda");
    free(str);
}


static void
test_str_starts_with(void **state)
{
    assert_true(sb_str_starts_with("bolaguda", "bola"));
    assert_true(sb_str_starts_with("bola", "bola"));
    assert_false(sb_str_starts_with("gudabola", "bola"));
    assert_false(sb_str_starts_with("guda", "bola"));
    assert_false(sb_str_starts_with("bola", "bolaguda"));
}


static void
test_str_ends_with(void **state)
{
    assert_true(sb_str_ends_with("bolaguda", "guda"));
    assert_true(sb_str_ends_with("bola", "bola"));
    assert_false(sb_str_ends_with("gudabola", "guda"));
    assert_false(sb_str_ends_with("guda", "bola"));
    assert_false(sb_str_ends_with("bola", "gudabola"));
}


static void
test_str_strip(void **state)
{
    char *str = sb_strdup("  \tbola\n  \t");
    assert_string_equal(sb_str_strip(str), "bola");
    free(str);
    str = sb_strdup("guda");
    assert_string_equal(sb_str_strip(str), "guda");
    free(str);
    assert_null(sb_str_strip(NULL));
}


static void
test_str_split(void **state)
{
    char **strv = sb_str_split("bola:guda:chunda", ':', 0);
    assert_string_equal(strv[0], "bola");
    assert_string_equal(strv[1], "guda");
    assert_string_equal(strv[2], "chunda");
    assert_null(strv[3]);
    sb_strv_free(strv);
    strv = sb_str_split("bola:guda:chunda", ':', 2);
    assert_string_equal(strv[0], "bola");
    assert_string_equal(strv[1], "guda:chunda");
    assert_null(strv[2]);
    sb_strv_free(strv);
    strv = sb_str_split("bola:guda:chunda", ':', 1);
    assert_string_equal(strv[0], "bola:guda:chunda");
    assert_null(strv[1]);
    sb_strv_free(strv);
    strv = sb_str_split("", ':', 1);
    assert_null(strv[0]);
    sb_strv_free(strv);
    assert_null(sb_str_split(NULL, ':', 0));
}


static void
test_str_replace(void **state)
{
    char *str = sb_str_replace("bolao", 'o', "zaz");
    assert_string_equal(str, "bzazlazaz");
    free(str);
    str = sb_str_replace("bolao", 'b', "zaz");
    assert_string_equal(str, "zazolao");
    free(str);
}


static void
test_strv_join(void **state)
{
    const char *pieces[] = {"guda","bola", "chunda", NULL};
    char *str = sb_strv_join(pieces, ":");
    assert_string_equal(str, "guda:bola:chunda");
    free(str);
    const char *pieces2[] = {NULL};
    str = sb_strv_join(pieces2, ":");
    assert_string_equal(str, "");
    free(str);
    assert_null(sb_strv_join(NULL, ":"));
}


static void
test_strv_length(void **state)
{
    char *pieces[] = {"guda","bola", "chunda", NULL};
    assert_int_equal(sb_strv_length(pieces), 3);
    char *pieces2[] = {NULL};
    assert_int_equal(sb_strv_length(pieces2), 0);
    assert_int_equal(sb_strv_length(NULL), 0);
}


static void
test_string_new(void **state)
{
    sb_string_t *str = sb_string_new();
    assert_non_null(str);
    assert_string_equal(str->str, "");
    assert_int_equal(str->len, 0);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
}


static void
test_string_free(void **state)
{
    sb_string_t *str = sb_string_new();
    free(str->str);
    str->str = sb_strdup("bola");
    str->len = 4;
    str->allocated_len = SB_STRING_CHUNK_SIZE;
    char *tmp = sb_string_free(str, false);
    assert_string_equal(tmp, "bola");
    free(tmp);
}


static void
test_string_append_len(void **state)
{
    sb_string_t *str = sb_string_new();
    str = sb_string_append_len(str, "guda", 4);
    assert_non_null(str);
    assert_string_equal(str->str, "guda");
    assert_int_equal(str->len, 4);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    str = sb_string_new();
    str = sb_string_append_len(str, "guda", 4);
    str = sb_string_append_len(str, "bola", 4);
    assert_non_null(str);
    assert_string_equal(str->str, "gudabola");
    assert_int_equal(str->len, 8);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    str = sb_string_new();
    str = sb_string_append_len(str, "guda", 3);
    str = sb_string_append_len(str, "bola", 4);
    assert_non_null(str);
    assert_string_equal(str->str, "gudbola");
    assert_int_equal(str->len, 7);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    str = sb_string_new();
    str = sb_string_append_len(str, "guda", 4);
    str = sb_string_append_len(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf", 600);
    str = sb_string_append_len(str, NULL, 0);
    str = sb_string_append_len(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf", 600);
    assert_non_null(str);
    assert_string_equal(str->str,
        "gudacwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjid"
        "zkcwnnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtax"
        "jiwaxfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqv"
        "evazdxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywh"
        "qcechgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxj"
        "rsbcsbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqd"
        "atnddxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvw"
        "srnrftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsf"
        "nwtgokxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexfcwlwmwxxmvjnwtidm"
        "jehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcwnnqhxhneolbwqlctc"
        "xmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwaxfhfyzymtffusoqyw"
        "aruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevazdxrewtgapkompnvii"
        "yielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcechgrwzaglzogwjvqnc"
        "jzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbcsbfvpylgjznsuhxcx"
        "oqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnddxntikgoqlidfnmdh"
        "xzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnrftzfeyasjpxoevypt"
        "pdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtgokxhegoifakimxbba"
        "fkeannglvsxprqzfekdinssqymtfexf");
    assert_int_equal(str->len, 1204);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE * 10);
    assert_null(sb_string_free(str, true));
}


static void
test_string_append(void **state)
{
    sb_string_t *str = sb_string_new();
    str = sb_string_append(str, "guda");
    assert_non_null(str);
    assert_string_equal(str->str, "guda");
    assert_int_equal(str->len, 4);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    str = sb_string_new();
    str = sb_string_append(str, "guda");
    str = sb_string_append(str, "bola");
    assert_non_null(str);
    assert_string_equal(str->str, "gudabola");
    assert_int_equal(str->len, 8);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    str = sb_string_new();
    str = sb_string_append(str, "guda");
    str = sb_string_append(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf");
    str = sb_string_append(str, NULL);
    str = sb_string_append(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf");
    assert_non_null(str);
    assert_string_equal(str->str,
        "gudacwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjid"
        "zkcwnnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtax"
        "jiwaxfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqv"
        "evazdxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywh"
        "qcechgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxj"
        "rsbcsbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqd"
        "atnddxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvw"
        "srnrftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsf"
        "nwtgokxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexfcwlwmwxxmvjnwtidm"
        "jehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcwnnqhxhneolbwqlctc"
        "xmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwaxfhfyzymtffusoqyw"
        "aruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevazdxrewtgapkompnvii"
        "yielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcechgrwzaglzogwjvqnc"
        "jzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbcsbfvpylgjznsuhxcx"
        "oqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnddxntikgoqlidfnmdh"
        "xzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnrftzfeyasjpxoevypt"
        "pdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtgokxhegoifakimxbba"
        "fkeannglvsxprqzfekdinssqymtfexf");
    assert_int_equal(str->len, 1204);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE * 10);
    assert_null(sb_string_free(str, true));
}


static void
test_string_append_c(void **state)
{
    sb_string_t *str = sb_string_new();
    str = sb_string_append_len(str, "guda", 4);
    for (int i = 0; i < 600; i++)
        str = sb_string_append_c(str, 'c');
    assert_non_null(str);
    assert_string_equal(str->str,
        "gudaccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
        "cccccccccccccccccccccccccccccccccccccccccccccccccccc");
    assert_int_equal(str->len, 604);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE * 5);
    assert_null(sb_string_free(str, true));
}


static void
test_string_append_printf(void **state)
{
    sb_string_t *str = sb_string_new();
    str = sb_string_append_printf(str, "guda: %s %d", "bola", 1);
    assert_non_null(str);
    assert_string_equal(str->str, "guda: bola 1");
    assert_int_equal(str->len, 12);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_strdup),
        unit_test(test_strndup),
        unit_test(test_strdup_printf),
        unit_test(test_str_starts_with),
        unit_test(test_str_ends_with),
        unit_test(test_str_strip),
        unit_test(test_str_split),
        unit_test(test_str_replace),
        unit_test(test_strv_join),
        unit_test(test_strv_length),
        unit_test(test_string_new),
        unit_test(test_string_free),
        unit_test(test_string_append_len),
        unit_test(test_string_append),
        unit_test(test_string_append_c),
        unit_test(test_string_append_printf),
    };
    return run_tests(tests);
}
