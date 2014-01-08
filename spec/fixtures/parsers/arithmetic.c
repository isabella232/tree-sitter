#include "parser.h"
#include "document.h"
#include <ctype.h>

enum ts_symbol {
    ts_symbol_expression,
    ts_symbol_term,
    ts_symbol_factor,
    ts_symbol_4,
    ts_symbol_3,
    ts_symbol_1,
    ts_symbol_2,
    ts_symbol_number,
    ts_symbol_variable,
    ts_symbol___END__
};

static const char *ts_symbol_names[] = {
    "expression",
    "term",
    "factor",
    "4",
    "3",
    "1",
    "2",
    "number",
    "variable",
    "__END__"
};

static void ts_lex(TSParser *parser) {
    START_LEXER();
    switch (LEX_STATE()) {
        case 0:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(3);
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(2);
            if (LOOKAHEAD_CHAR() == '(')
                ADVANCE(1);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_symbol_1);
        case 2:
            if (isdigit(LOOKAHEAD_CHAR()))
                ADVANCE(2);
            ACCEPT_TOKEN(ts_symbol_number);
        case 3:
            if (isalnum(LOOKAHEAD_CHAR()))
                ADVANCE(3);
            ACCEPT_TOKEN(ts_symbol_variable);
        case 4:
            LEX_ERROR();
        case 5:
            if (LOOKAHEAD_CHAR() == '+')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            ACCEPT_TOKEN(ts_symbol_4);
        case 7:
            if (LOOKAHEAD_CHAR() == '*')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            ACCEPT_TOKEN(ts_symbol_3);
        case 9:
            if (LOOKAHEAD_CHAR() == ')')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(ts_symbol_2);
        default:
            LEX_ERROR();
    }
    FINISH_LEXER();
}

static TSTree * ts_parse(const char *input) {
    START_PARSER();
    switch (PARSE_STATE()) {
        case 0:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(5);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_1:
                    SHIFT(9);
                case ts_symbol_term:
                    SHIFT(2);
                case ts_symbol_expression:
                    SHIFT(1);
                default:
                    PARSE_ERROR();
            }
        case 1:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol___END__:
                    ACCEPT_INPUT();
                default:
                    PARSE_ERROR();
            }
        case 2:
            SET_LEX_STATE(5);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_4:
                    SHIFT(3);
                default:
                    REDUCE(ts_symbol_expression, 1);
            }
        case 3:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(5);
                case ts_symbol_1:
                    SHIFT(9);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_term:
                    SHIFT(4);
                default:
                    PARSE_ERROR();
            }
        case 4:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_expression, 3);
            }
        case 5:
            SET_LEX_STATE(7);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_3:
                    SHIFT(6);
                default:
                    REDUCE(ts_symbol_term, 1);
            }
        case 6:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_1:
                    SHIFT(9);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(7);
                default:
                    PARSE_ERROR();
            }
        case 7:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_term, 3);
            }
        case 8:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_factor, 1);
            }
        case 9:
            SET_LEX_STATE(0);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_variable:
                    SHIFT(8);
                case ts_symbol_factor:
                    SHIFT(5);
                case ts_symbol_number:
                    SHIFT(8);
                case ts_symbol_1:
                    SHIFT(9);
                case ts_symbol_term:
                    SHIFT(2);
                case ts_symbol_expression:
                    SHIFT(10);
                default:
                    PARSE_ERROR();
            }
        case 10:
            SET_LEX_STATE(9);
            switch (LOOKAHEAD_SYM()) {
                case ts_symbol_2:
                    SHIFT(11);
                default:
                    PARSE_ERROR();
            }
        case 11:
            SET_LEX_STATE(4);
            switch (LOOKAHEAD_SYM()) {
                default:
                    REDUCE(ts_symbol_factor, 3);
            }
        default:
            PARSE_ERROR();
    }
    FINISH_PARSER();
}

void TSDocumentSetUp_arithmetic(TSDocument *document) {
    TSDocumentSetUp(document, ts_parse, ts_symbol_names);
}