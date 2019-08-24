/*
 * squareball: A general-purpose library for C99.
 * Copyright (C) 2014-2018 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file LICENSE.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include <squareball/sb-strfuncs.h>
#include <squareball/sb-string.h>

#define SB_STRING_CHUNK_SIZE 128


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
    assert_null(sb_string_free(NULL, false));
}


static void
test_string_dup(void **state)
{
    sb_string_t *str = sb_string_new();
    free(str->str);
    str->str = sb_strdup("bola");
    str->len = 4;
    str->allocated_len = SB_STRING_CHUNK_SIZE;
    sb_string_t *new = sb_string_dup(str);
    assert_non_null(new);
    assert_string_equal(new->str, "bola");
    assert_int_equal(new->len, 4);
    assert_int_equal(new->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(new, true));
    assert_null(sb_string_free(str, true));
    assert_null(sb_string_dup(NULL));
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
    str = sb_string_new();
    str = sb_string_append_len(str, NULL, 0);
    assert_non_null(str);
    assert_string_equal(str->str, "");
    assert_int_equal(str->len, 0);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    assert_null(sb_string_append_len(NULL, "foo", 3));
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
    str = sb_string_new();
    str = sb_string_append(str, NULL);
    assert_non_null(str);
    assert_string_equal(str->str, "");
    assert_int_equal(str->len, 0);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    assert_null(sb_string_append(NULL, "asd"));
    assert_null(sb_string_append(NULL, NULL));
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
    assert_null(sb_string_append_c(NULL, 0));
}


static void
test_string_append_printf(void **state)
{
    sb_string_t *str = sb_string_new();
    str = sb_string_append_printf(str, NULL);
    assert_string_equal(str->str, "");
    assert_non_null(str);
    str = sb_string_append_printf(str, "guda: %s %d", "bola", 1);
    assert_non_null(str);
    assert_string_equal(str->str, "guda: bola 1");
    assert_int_equal(str->len, 12);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    assert_null(sb_string_append_printf(NULL, "asd"));
}


static void
test_string_append_escaped(void **state)
{
    sb_string_t *str = sb_string_new();
    str = sb_string_append_escaped(str, NULL);
    assert_non_null(str);
    assert_string_equal(str->str, "");
    assert_int_equal(str->len, 0);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    str = sb_string_append_escaped(str, "foo \\a bar \\\\ lol");
    assert_non_null(str);
    assert_string_equal(str->str, "foo a bar \\ lol");
    assert_int_equal(str->len, 15);
    assert_int_equal(str->allocated_len, SB_STRING_CHUNK_SIZE);
    assert_null(sb_string_free(str, true));
    assert_null(sb_string_append_escaped(NULL, "asd"));
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_string_new),
        unit_test(test_string_free),
        unit_test(test_string_dup),
        unit_test(test_string_append_len),
        unit_test(test_string_append),
        unit_test(test_string_append_c),
        unit_test(test_string_append_printf),
        unit_test(test_string_append_escaped),
    };
    return run_tests(tests);
}
