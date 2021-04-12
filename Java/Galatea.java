
/*
We will call a sequence of integers a spike if they first increase (strictly) and then decrease (also strictly, including the last element of the increasing part).
For example 4, 5, 7, 6, 3, 2) is a spike, but (1,1,5, 4,3) and (1,4,3,5) are not. Note that the increasing and decreasing parts always intersect, e.g.: for spike (3,5, 2) sequence (3,5) is an increasing part and sequence (5,2) is a decreasing part, and for spike (2) sequence (2) is both an increasing and a decreasing part Your are given an array A of N integers.

Your task is to calculate the length of the longest possible spike, which can be created from numbers from array A. Note that you are NOT supposed to find the longest spike as a sub-sequence of A, but rather choose some, numbers from A and reorder them to create the longest spike.

Write a function:
class Solution { public int solution(int[] A); }
which, given an array A of integers of length N, returns the length of the longest spike which can be created from the numbers from A.

Examples:

Given A = [1, 2], your function should return 2, because (1, 2) is already a spike.
Given A = [2,5, 3, 2, 4, 1), your function should return 6, because we can create the following spike of length 6: (2,4,5, 3, 2, 1).
Given A = [2,3,3,2, 2, 2, 1), your function should return 4, because we can create the following spike of length 4: (2, 3, 2, 1) and we cannot create any longer spike. Note that increasing and decreasing parts should be strictly increasing/decreasing and they always intersect. Write an efficient algorithm for the following assumptions:
• N is an integer within the range (1..100,000); • each element of array A is an integer within the range, [1..1,000,000).




*
* You are given two passages of text that have been scanned and passed through OCR software. (OCR stands for Optical Character Recognition, whi is the conversion of printed text into machine-readable strings.) Unfortunately, the scans were of poor quality and some letters were not recognized by the OCR software. Write a program to check (based on the output from the OCR software) whether the two text sources might in fact b the same.

We assume that each text passage consists only of English letters. The OCH output from each scan is given as a string in which unrecognized letters are marked as follows. Firstly, let us mark each unrecognized letter by“?'.

For example, if the OCR software didn't recognize the second and third letters of the text "Apple", it would result in OCR output of 'A??Le'. Then, for brevity, every group of K consecutive "?" characters is replaced by the decimal representation of integer K (without leading zeros). Thus, the above OCR result would be represented as "A2Le'. (For the sake of clarity, such numeric replacement is performed on groups of "?" characters that cannot be extended either to the left or to the right.)

You are given two strings S and T consisting of N and M characters, respectively, and you would like to check whether they might have been obtained as OCR scans of the same text. For example, both strings 'A2Le and "2pL1" could have been obtained as scans of the word "Apple" (but also as scans of the word "AmpLe“). Both strings "ale" and "10a' could have been obtained as scans of the word 'abbbbbbbbba" (but also from many other strings of length 11, starting and ending with "a"). On the other hand, strings "bal' and '1Ad could not have been obtained from the same.

Write a function:
class Solution { public boolean solution(String S, String T); }
that, given two strings S and T consisting of N and M characters, respectively, determines whether strings S and T can be obtained as OCR output from the same text.
For example, given "A2Le" and "2pL1", your function should return true, as explained above. Given "a10" and "10a", your function should return true, as explained above. Given "bal" and "1Ad", your function should return false, as explained above. Given "3x2x" and "8", your function should return false, since they represent strings of different length.
Assume that:
• N and M are integers within the range (1..100,000;
lengths of texts before the OCR process are integers within the range (1..100,000); strings S and T consist only of alphanumerical characters (a-z
and/or A-Z and/or 8-9); • strings S and T contain neither single zeros (e.g. "abc@abc"),
nor integers with leading zeros (e.g. "abce12abc").
*
* */



import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;


public class Main {

    public static int Solution(int[] A){

        // with the given description, there has to be 1 which only occurs once. All other elements can occur at most twice (left and right)
        //therefore get occurance of all elements. Count them up with ignoring 2+ occurances and count max as one occurance should give us the size.

        int n = 0;

        //get size
        int size = A.length;
        //no element case
        if(size == 0)
            return n;

        //count the occurance of each unique number
        Map<Integer, Integer> occurance = new HashMap<Integer, Integer>();
        for (int item:A) {
            int count = 0;
            if(occurance.containsKey(item))
                count = occurance.get(item);
            occurance.put(item,count+1);
        }

        //finding the peak element and only counting once
        int max = Arrays.stream(A).max().getAsInt();
        occurance.put(max,1);

        //counting all element occurance
        for (Map.Entry<Integer,Integer> entry : occurance.entrySet()){
            int _value = entry.getValue();
            if(_value>2)
                n+=2;
            else n+=_value;
        }


        return n;
    }

    public static boolean solution(String S, String T) {
        // write your code in Java SE 8

        // the text being identical means they came from the same source
        if(S.equals(T))
            return true;


        //Lets pick S as our main string and match char by char with T, accounting for tolerance if we face a digit
        int tIndex = 0;
        int t_missings = 0;

        int sCount = 0;
        int tCount =0;

        for (int i=0; i<S.length(); i++)
        {
            if(tIndex>T.length())
                return false;
            //Is S missing at this position
            if(Character.isDigit(S.charAt(i)))
            {
                int _missing = Character.getNumericValue(S.charAt(i));
                sCount+= _missing;
                //there has to be at least _missing more characters
                for (int k =0; k<_missing; k++)
                {
                    if(tIndex>T.length())
                        return false;
                    if(!Character.isDigit(T.charAt(tIndex)))
                    {
                        tCount++;
                        t_missings = 0;
                        tIndex++;
                        continue;
                    }
                    else if (T.charAt(tIndex) == '?')
                    {
                        tCount++;
                        t_missings = 0;
                        tIndex++;
                        continue;
                    }
                    else if(Character.isDigit(T.charAt(tIndex))){
                        t_missings++;
                        int _missingDigit = Character.getNumericValue(T.charAt(tIndex));
                        tCount++;
                        if(t_missings>_missingDigit)
                            return false;
                        if(t_missings==_missingDigit)
                            tIndex++;
                    }
                    else return false;
                }


            }

            //S has a digit, check if its compatible with T
            else{
                sCount++;
                //this digit must be equal to t's position digit or has to be missing or ?

                //is it equal to t's position digit?
                if(S.charAt(i) == T.charAt(tIndex))
                {
                    tCount++;
                    t_missings = 0;
                    tIndex++;
                    continue;
                }
                //check if its just a question mark meaning a character here
                if(T.charAt(tIndex) == '?')
                {
                    tCount++;
                    t_missings = 0;
                    tIndex++;
                    continue;
                }
                // check if its missing at this position
                else if(Character.isDigit(T.charAt(tIndex))){
                    t_missings++;
                    int _missingDigit = Character.getNumericValue(T.charAt(tIndex));
                    tCount++;
                    if(t_missings>_missingDigit)
                        return false;
                    if(t_missings==_missingDigit)
                        tIndex++;
                    continue;
                }
                else return false;

            }
            if(tIndex<t_missings)
                return false;
        }
        return true;
    }
    public static void main(String[] args) {
        System.out.println(solution( "10a","a10"));
    }
}
