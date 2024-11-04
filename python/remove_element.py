class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        j = 0  # Position to place the next non-val element
        for i in range(len(nums)):
            if nums[i] != val:  # Only do something if nums[i] is not equal to val
                nums[j] = nums[i]  # Move the element to the front part of the list
                j += 1  # Increment j to indicate the next position for a non-val element
        return j  # j is now the count of elements not equal to val

