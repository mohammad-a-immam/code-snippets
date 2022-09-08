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

        public int MaxProfit(int[] prices)
        {
            if (prices.Length < 2)
                return 0;

            int buy = 0;
            int sell = 1;
            int maxProfit = 0;

            while (sell < prices.Length)
            {

                var currentProfit = prices[sell] - prices[buy];
                if (prices[buy] > prices[sell])
                {
                    buy = sell;
                }

                else if (currentProfit > maxProfit)
                {
                    maxProfit = currentProfit;

                }
                sell++;
            }

            return maxProfit;
        }

        //bad solution
        /*public int MaxProfit(int[] prices)
        {
            if (prices.Length < 2)
                return 0;

            int buy = prices[0];
            int sell = prices[1];


            for (int i = 0; i < prices.Length; i++)
            {
                if (prices[i] <= buy)
                {
                    //check profit
                    for (int j = i + 1; j < prices.Length; j++)
                    {
                        if (prices[j] - prices[i] > sell - buy)
                        {
                            buy = prices[i];
                            sell = prices[j];
                        }
                    }
                }


            }

            if (buy > sell)
                return 0;

            return sell - buy;
        }*/


        /*public int MaxProfit(int[] prices)
        {
            if (prices.Length < 2)
                return 0;

            int buy = prices[0];
            int sell = prices[1];

            int maxProfit = sell - buy;



            for (int i = 0; i < prices.Length; i++)
            {

                //check profit
                for (int j = i + 1; j < prices.Length; j++)
                {
                    if (prices[j] - prices[i] > maxProfit)
                    {
                        buy = prices[i];
                        sell = prices[j];
                        maxProfit = sell - buy;
                    }
                }



            }

            if (buy >= sell)
                return 0;


            return sell - buy;
        }*/
    }


}
