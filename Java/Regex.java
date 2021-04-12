package plc.homework;

import java.util.regex.Pattern;

/**
 * Contains {@link Pattern} constants, which are compiled regular expressions.
 * See the assignment page for resources on regexes as needed.
 */
public class Regex {

    public static final Pattern
            EMAIL = Pattern.compile("[A-Za-z0-9._\\-]+@[A-Za-z0-9-]*\\.[a-z]{2,3}"),

            //Strings between 10 and 20 characters (inclusive) which have even lengths.
            //The allowed characters here are not specified, and should be considered unrestricted - maybe there's something in regex for this?
            EVEN_STRINGS = Pattern.compile("(..){5,10}"), //TODO

                //Integer List: A list of comma-separated, positive integers surrounded by square brackets []. A optional single space character is allowed after the comma.
            INTEGER_LIST = Pattern.compile("\\[(([0-9],|[0-9], )*[0-9])*\\]"), //TODO

                //Number: An integer or decimal number. Leading or trailing decimals are not allowed. An optional sign (+/-) is allowed.
            NUMBER = Pattern.compile("[\\+\\-]?([0-9]+[0-9\\.]*)*[0-9]"), //TODO

                //String: A double-quoted string literal. Escape characters are supported starting with a backslash followed by bnrt
            STRING = Pattern.compile("\\\"([^\\\\\"]*|(\\\\[bnrt\\'\\\\])*)*\\\""); //TODO

}
