int  removeElement(int*  nums,    int  numsLength,  int  val){
	int cnt = 0;
	for(int i = 0; i < numsLength; ++i){
		if(nums[i] == val) cnt++;
		else nums[i-cnt] = nums[i];
	}
	return numsLength - cnt;
}