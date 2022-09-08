using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Coding_Challenges
{
    class Sums
    {

        /// <summary>
        /// Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).
        /// Return the running sum of nums.
        /// </summary>
        public int[] RunningSum(int[] nums)
        {
            var result = new int[nums.Length];

            for (int i = 0; i < nums.Length; i++)
            {
                var sum = 0;
                for (int j = 0; j <= i; j++)
                {
                    sum += nums[j];
                }
                result[i] = sum;
            }

            return result;
        }
    }
}
