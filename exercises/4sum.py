
def fourSum(nums, target):
    nums.sort()
    n = len(nums)
    ans = []
    for i in range(n):
        for j in range(i+1, n):
            l, r = j + 1, n - 1
            remain = target - nums[i] - nums[j]
            while l < r:
                if nums[l] + nums[r] == remain:
                    ans.append((nums[i], nums[j], nums[l], nums[r]))
                    l += 1
                    r -= 1
                elif nums[l] + nums[r] > remain:
                    r -= 1
                else:
                    l += 1
    return ans
print(fourSum([-3,-1,0,3,2,1,4], 2))