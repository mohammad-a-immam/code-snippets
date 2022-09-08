using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Coding_Challenges
{
    class LinkedList
    {
        // Definition for singly-linked list.
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

        public ListNode ReverseList(ListNode head)
        {
            if (head == null)
                return null;

            if (head.next == null)
                return head;

            var _temp = head.next;
            var current = head;
            head.next = null;

            while (_temp != null)
            {
                var _next = _temp.next;
                _temp.next = current;
                current = _temp;
                _temp = _next;
            }

            return current;
        }

        public ListNode MiddleNode(ListNode head)
        {
            int runningCount = 1;
            ListNode middle = head;

            while (head.next != null)
            {
                runningCount++;
                if (runningCount == 2)
                {
                    middle = middle.next;
                    runningCount = 0;
                }
                head = head.next;
            }

            return middle;
        }

        public ListNode DetectCycle(ListNode head)
        {
            if (head == null)
                return null;
            List<ListNode> visited = new List<ListNode>();

            while (head.next != null)
            {
                if (visited.Contains(head.next))
                    return head.next;
                visited.Add(head);
                head = head.next;
            }

            return null;
        }
    }
}