using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Coding_Challenges
{
    // * Definition for a binary tree node.
  public class TreeNode {
      public int val;
      public TreeNode left;
      public TreeNode right;
      public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
          this.val = val;
          this.left = left;
          this.right = right;
      }
  }
    public static class Tree
    {
        public static string Tree2str(TreeNode root)
        {
            if (root == null)
                return "";
            string leftResult = Tree2str(root.left);
            leftResult = String.IsNullOrEmpty(leftResult) ? leftResult: "(" + leftResult + ")";
            string rightResult = Tree2str(root.right);
            rightResult = String.IsNullOrEmpty(rightResult) ? rightResult : "(" + rightResult + ")";
            return root.val + leftResult + rightResult;
        }
    }
}
