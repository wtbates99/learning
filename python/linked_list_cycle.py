# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def hasCycle(self, head: ListNode) -> bool:
        # If the list is empty or has only one element, it can't have a cycle
        if not head or not head.next:
            return False
        
        # Start both pointers at the beginning
        slow = head  # moves one step at a time
        fast = head.next  # moves two steps at a time

        # Traverse the list
        while fast and fast.next:
            # If slow meets fast, there is a cycle
            if slow == fast:
                return True
            
            # Move slow by one step
            slow = slow.next
            # Move fast by two steps
            fast = fast.next.next
        
        # If we reach here, fast reached the end of the list, so there's no cycle
        return False

