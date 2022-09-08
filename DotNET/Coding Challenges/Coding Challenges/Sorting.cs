using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Coding_Challenges
{
    class Sorting
    {
        public class ListNode
        {
            public int val;
            public ListNode next;

            public ListNode(int val = 0, ListNode next = null)
            {
                this.val = val;
                this.next = next;
            }
        }

        /// <summary>
        /// Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
        /// </summary>
        /// <param name="list1"></param>
        /// <param name="list2"></param>
        /// <returns></returns>
        public ListNode MergeTwoLists(ListNode list1, ListNode list2)
        {
            if (list1 == null && list2 == null)
                return null;

            ListNode resultHead = new ListNode();
            ListNode resultC = resultHead;

            while (list1 != null && list2 != null)
            {
                if (list1.val < list2.val)
                {
                    resultC.val = list1.val;
                    list1 = list1.next;
                    if (list1 != null || list2 != null)
                    {
                        resultC.next = new ListNode();
                        resultC = resultC.next;
                    }
                }
                else if (list2.val < list1.val)
                {
                    resultC.val = list2.val;
                    list2 = list2.next;
                    if (list1 != null || list2 != null)
                    {
                        resultC.next = new ListNode();
                        resultC = resultC.next;
                    }
                }
                else if (list1.val == list2.val)
                {
                    resultC.val = list1.val;
                    list1 = list1.next;
                    if (list1 != null || list2 != null)
                    {
                        resultC.next = new ListNode();
                        resultC = resultC.next;
                    }

                    resultC.val = list2.val;
                    list2 = list2.next;
                    if (list1 != null || list2 != null)
                    {
                        resultC.next = new ListNode();
                        resultC = resultC.next;
                    }
                }
            }

            while (list1 != null)
            {
                resultC.val = list1.val;
                list1 = list1.next;
                if (list1 != null || list2 != null)
                {
                    resultC.next = new ListNode();
                    resultC = resultC.next;
                }
            }

            while (list2 != null)
            {
                resultC.val = list2.val;
                list2 = list2.next;
                if (list1 != null || list2 != null)
                {
                    resultC.next = new ListNode();
                    resultC = resultC.next;
                }
            }

            return resultHead;
        }
    }
}