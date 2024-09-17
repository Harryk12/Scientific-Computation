int main() {
  //find the maximum sequence length over all starting points
  int max_length=0;
  //go over all starting points, find length, update max if needed
  for(int start=2;start<1000;start++){
    //find the length from this starting points, and udpate max if needed
    int length=0;
    //do the sequence until you hit 1, updating length in the process
    for (int current=start;current!=1; ){
      //update length
      length+=1;
      if (length>max_length)...
      //update current
	if (....)(....);
    }

  }

  
  return 0;
}
