#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>

/**
 * The namespace to be used when printing on the console.
 */
namespace util {

    /**
     * The space character.
     */
    static const char SPACE = ' ';

    /**
     * The separator block.
     */
    static const char* SEPARATOR =
            "------------------------------------------------------------------------------------------------------------\n";

    /**
     * The width of a large column.
     */
    static const int LARGE_COL_WIDTH = 20;

    /**
     * The width of a small column.
     */
    static const int SMALL_COL_WIDTH = 15;

    /**
     * Checks if a string is a digit. Negative numbers are rejected.
     *
     * @param str the string
     * @param acceptFloat true, if it accepts float numbers; false, otherwise
     * @return  true, if it is a digit; false, otherwise
     */
    bool isdigit(const std::string& str, bool acceptFloat = false);

    /**
     * Checks if a string contains another string.
     *
     * @param str the string
     * @param expected the string expected to find
     * @return true, if the strings contains the expected string; false, otherwise
     */
    bool contains(const std::string& str, const std::string& expected);

    /**
     * Makes sure there aren't unneeded spaces and that just the first letter is uppercase.
     *
     * @param str the string
     */
    void normalize(std::string& str);

    /**
     * Converts all the letters in the string to lowercase.
     *
     * @param str the string
     */
    void lowercase(std::string& str);

    /**
     * Converts all the letters in the string to uppercase.
     *
     * @param str the string
     */
    void uppercase(std::string& str);

    /**
     * Converts a float to a string.
     *
     * @param n the float
     * @return the float converted to a string
     */
    std::string to_string (float n);

    /**
     * Separates each word in the string by a column.
     *
     * @param str the string
     * @param large true, if it the column width is large; false, otherwise
     * @return the string separated by columns
     */
    std::string column(std::string str, bool large = false);

    /**
     * Gets a list with all the words in a string.
     *
     * @param input the string
     * @return the list of all the words in the string
     */
    std::vector<std::string> to_words(const std::string& input);

    /**
     * The ANSI announce color.
     */
    static const char* ANSI_ANNOUNCE_COLOR = "\033[38;5;";

    /**
     * The ANSI to reset console.
     */
    static const char* ANSI_RESET_CONSOLE = "\033[0m";

    /**
     * The ANSI to clear screen.
     */
    static const char* ANSI_CLEAR_SCREEN = "\x1B[2J\x1B[H";

    /**
     * The color blue.
     */
    static const int BLUE = 6;

    /**
     * Clears screen.
     */
    void clearScreen();

    /**
     * Prints a string in a certain color.
     *
     * @param s the string
     * @param color the color
     */
    void print(const std::string& s, int color);

    /**
     * Erase Windows carriage return char from the string.
     * @param line - string to be manipulated.
     */
    void stripCarriageReturn(std::string& line);
}

#endif //FEUP_AEDA_PROJECT_UTIL_H
