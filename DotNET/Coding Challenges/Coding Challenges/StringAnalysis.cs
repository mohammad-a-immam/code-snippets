using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Coding_Challenges
{
    class StringAnalysis
    {
        /// <summary>
        /// Two strings s and t are isomorphic if the characters in s can be replaced to get t.
        /// All occurrences of a character must be replaced with another character while preserving the order of characters.No two characters may map to the same character, but a character may map to itself.
        /// </summary>
        /// <param name="s"></param>
        /// <param name="t"></param>
        /// <returns></returns>

        //Not working solution
        public bool IsIsomorphic(string s, string t)
        {
            //if the strings are not equilength
            if (s.Length != t.Length)
                return false;

            Dictionary<char, char> map_st = new Dictionary<char, char>();
            Dictionary<char, char> map_ts = new Dictionary<char, char>();

            //map all letters in s to t
            for (var i = 0; i < s.Length; i++)
            {
                var letter = s[i];
                map_st[letter] = t[i];
            }

            //map all letters in t to s
            for (var i = 0; i < t.Length; i++)
            {
                var letter = t[i];
                map_ts[letter] = s[i];
            }

            //check if the number of letters are the same
            if (map_st.Count != map_ts.Count)
                return false;

            //now check if the mappings align
            for (int i = 0; i < s.Length; i++)
            {
                if (map_st[s[i]] != t[i])
                    return false;
                if (map_ts[t[i]] != s[i])
                    return false;
            }

            return true;
        }

        public bool IsSubsequence(string s, string t)
        {

            var lettersAnalyzed = -1;
            foreach (var sLetter in s)
            {
                var letterFound = false;
                for (int j = lettersAnalyzed + 1; j < t.Length; j++)
                {
                    if (sLetter == t[j])
                    {
                        letterFound = true;
                        lettersAnalyzed = j;
                        break;
                    }
                }
                if (!letterFound)
                    return false;
            }

            return true;
        }
    }
}
