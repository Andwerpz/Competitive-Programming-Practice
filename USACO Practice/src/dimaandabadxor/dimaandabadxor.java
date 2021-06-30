
//package dimaandabadxor;

import java.util.*;
import java.io.*;

public class dimaandabadxor {
  public static void main(String[] args) throws IOException {
	  
	  //1151B
	  
	  //all you have to do is pick one number from each row. If the xor is equal to 0, and there is a row where you can pick a different number, then pick that number, and the xor will not be 0. 
	  //If there is no row where you can pick a different number, then the xor has to be 0. 
	  
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    int[][][] dp = new int[n][1024][2];	//0 : current num's column index, 1 : previous nums' dp index
    for(int i = 0; i < n; i++){
    	for(int j = 0; j < dp[0].length; j++) {
    		Arrays.fill(dp[i][j], -1);
    	}
    	
    }
    int[][] nums = new int[n][m];
    for(int i = 0; i < n; i++){
      st = new StringTokenizer(fin.readLine());
      for(int j = 0; j < m; j++){
        nums[i][j] = Integer.parseInt(st.nextToken());
      }
    }
    for(int i = 0; i < n; i++){
      if(i == 0){
        for(int j = 0; j < m; j++){
          dp[0][nums[0][j]][0] = j;
        }
      }
      else{
        for(int j = 0; j < dp[0].length; j++){
          if(dp[i - 1][j][0] != -1){
            int base = j;
            for(int k = 0; k < m; k++){
              int next = base ^ nums[i][k];
              dp[i][next][1] = base;
              dp[i][next][0] = k;
            }
          }
        }
      }
//      for(int[][] j : dp) {
//    	  for(int[] k : j) {
//    		  System.out.print(k[0] + " " + k[1] + ", ");
//    	  }
//    	  System.out.println();
//      }
//      System.out.println();
    }
    boolean isValid = false;
    int which = 0;
    for(int i = 1; i < dp[0].length; i++) {
    	//System.out.println(dp[n - 1][i] + " " + m);
      if(dp[n - 1][i][0] != -1){
        isValid = true;
        which = i;
        break;
      }
    }
    if(isValid){
      StringBuilder fout = new StringBuilder();
      fout.append("TAK\n");
      int[] ans = new int[n];
      for(int i = n - 1; i >= 0; i--){
        ans[i] = dp[i][which][0];
        which = dp[i][which][1];
      }
      for(int i = 0; i < n; i++) {
    	  fout.append(ans[i] + 1).append(" ");
      }
      System.out.println(fout);
    }
    else{
      System.out.println("NIE");
    }
  }

}
