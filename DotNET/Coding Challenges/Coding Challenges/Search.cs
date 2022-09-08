using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Coding_Challenges
{
    public class Search
    {
        //Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums.
        //If target exists, then return its index. Otherwise, return -1.
        public int BinarySearch(int[] nums, int target)
        {
            //start at mid
            int index = Math.Abs(nums.Length / 2);
            int item = nums[index];

            if (item == target)
                return index;

            if (index <= 0)
                return -1;

            else if (item < target)
            {
                int[] list = new int[nums.Length - index];
                int listIndex = 0;
                for (int i = index; i < nums.Length; i++)
                {
                    list[listIndex] = nums[i];
                    listIndex++;
                }

                int _tempIndex = BinarySearch(list, target);
                return _tempIndex == -1 ? -1 : index + _tempIndex;
            }

            else if (item > target)
            {
                int[] list = new int[nums.Length - index];
                int listIndex = 0;
                for (int i = 0; i < index; i++)
                {
                    list[listIndex] = nums[i];
                    listIndex++;
                }

                return BinarySearch(list, target);
            }

            return -1;

        }

        public int PivotIndex(int[] nums)
        {

            for (int i = 0; i < nums.Length; i++)
            {
                var leftSum = 0;
                for (int j = 0; j < i; j++)
                {
                    leftSum += nums[j];
                }
                var rightSum = 0;
                for (int j = i + 1; j < nums.Length; j++)
                {
                    rightSum += nums[j];
                }

                if (leftSum == rightSum)
                    return i;
            }
            return -1;
        }
    }
}