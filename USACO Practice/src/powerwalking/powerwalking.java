//package powerwalking;

import java.util.*;
import java.io.*;

public class powerwalking {
	public static void main(String[] args) throws IOException {
		
		//1642B
		
		//since you want the minimum power sum, you want to give each kid the minimum amount of unique powerups.
		
		//the observation is that if you have multiple of the same powerup, you want to avoid giving the same powerup
		//to different kids, as this will raise your power sum. 
		
		//notice that if you have 'a' different types of powerups, from 1 to 'a' kids, you can give each of them all
		//of a certain type of powerup. But from 'a' to 'n' kids, you have to start giving different kids the same powerup,
		//increasing your sum by 1 for each extra kid.
		
		//so from 1 - 'a', the answer is 'a', and from 'a' to 'n', the answer increases by 1 for every extra kid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			Integer[] nums = new Integer[n];
			HashMap<Integer, Integer> v = new HashMap<Integer, Integer>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				v.put(nums[i], v.getOrDefault(nums[i], 0) + 1);
			}
			int ans = v.size();
			for(int i = 0; i < v.size(); i++) {
				fout.append(ans).append(" ");
			}
			for(int i = v.size(); i < n; i++) {
				ans ++;
				fout.append(ans).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
