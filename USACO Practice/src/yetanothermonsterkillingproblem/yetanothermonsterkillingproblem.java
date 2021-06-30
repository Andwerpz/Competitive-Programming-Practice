//package yetanothermonsterkillingproblem;

import java.util.*;
import java.io.*;

public class yetanothermonsterkillingproblem {

  static ArrayList<ArrayList<Integer>> tree;

  public static int getMaxInRange(int low, int high){
    int ans = 0;
    for(int i = low; i <= high; i += 0){
      int index = i;
      int layer = 0;
      int increment = 1;
      while(true){
        int temp = index;
        index /= 2;
        layer ++;
        increment *= 2;
        int l = index * increment;
        int h = l + increment;
        if(l < low || h > high){
          index = temp;
          layer --;
          increment /= 2;
          break;
        }
      }
      i += increment;
      ans = Math.max(ans, tree.get(layer).get(index));
    }
    return ans;
  }

  public static void main(String[] args) throws IOException {
	  
	  //1257D
	  
	  //use pfx to sort the heroes by endurance, and segment tree to get max power of segment with monsters. Each day, try to kill the most amount of monsters possible.
	  
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    int t = Integer.parseInt(fin.readLine());
    StringBuilder fout = new StringBuilder();
    while(t-- > 0){
      tree = new ArrayList<ArrayList<Integer>>();
      int maxMonsterPower = 0;
      int maxHeroPower = 0;
      int n = Integer.parseInt(fin.readLine());
      int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(n) / Math.log(2))));
      StringTokenizer st = new StringTokenizer(fin.readLine());
      for(int i = 0; i < treeSize; i++){
        int next = -1;
        if(i < n){
          next = Integer.parseInt(st.nextToken());
          maxMonsterPower = Math.max(maxMonsterPower, next);
        }
        int layer = 0;
        while(true){
          if(layer == tree.size()){
            tree.add(new ArrayList<Integer>());
          }
          if(layer == 0){
            tree.get(0).add(next);
          }
          else {
            int size = tree.get(layer - 1).size();
            int a = tree.get(layer - 1).get(size - 1);
            int b = tree.get(layer - 1).get(size - 2);
            tree.get(layer).add(Math.max(a, b));
          }
          if(tree.get(layer).size() % 2 == 0){
            layer ++;
          }
          else {
            break;
          }
        }
      }
      int m = Integer.parseInt(fin.readLine());
      int[][] h = new int[m][2]; 
      for(int i = 0;i < m ; i++){
        st = new StringTokenizer(fin.readLine());
        h[i][0] = Integer.parseInt(st.nextToken()); //power
        h[i][1] = Integer.parseInt(st.nextToken()); //endurance
        maxHeroPower = Math.max(h[i][0], maxHeroPower);
      }
      Arrays.sort(h, (a, b) -> b[1] - a[1]);
      TreeMap<Integer, Integer> power = new TreeMap<Integer, Integer>();
      int maxPower = 0;
      for(int i = 0; i < m; i++){
        maxPower = Math.max(h[i][0], maxPower);
        h[i][0] = maxPower;
        power.put(h[i][1], h[i][0]);
      }
      //System.out.println(power);
      if(maxMonsterPower <= maxHeroPower) {
    	  int pointer = 0;
	      int ans = 0;
	      int minEndurance = power.firstKey();
	      int maxEndurance = power.lastKey();
	      //System.out.println(maxEndurance + " " + minEndurance);
	      while(pointer < n){
	    	  //System.out.println(pointer);
	        int low = minEndurance;
	        int high = maxEndurance;
	        int mid = low + (high - low) / 2;
	        int maxAns = 0;
	        //System.out.println("POINTER: " + pointer);
	        while(low <= high){
	          int curPower = power.ceilingEntry(mid).getValue();
	          int monsterPower = getMaxInRange(pointer, Math.min(pointer + mid - 1, treeSize - 1));
	          //System.out.println(curPower + " " + monsterPower);
	          if(curPower >= monsterPower){
	            maxAns = Math.max(mid, maxAns);
	            low = mid + 1;
	          }
	          else{
	            high = mid - 1;
	          }
	          mid = low + (high - low) / 2;
	        }
	        //System.out.println(pointer + " " + maxAns);
	        pointer += maxAns;
	        ans ++;
	      }
	      fout.append(ans).append("\n");
      }
      else {
    	  fout.append("-1\n");
      }
      
    } 
    System.out.print(fout);
  }
}
