//package weirdsum;

import java.util.*;
import java.io.*;

public class weirdsum {
	public static void main(String[] args) throws IOException {
		
		//1649C
		
		//since we're dealing with manhattan distance, we can consider the x and y distances separately. 
		
		//a naive solution would be to store the sum of distance for every color, and the count of each color
		//met so far. When moving to the next layer, just add the count of each color to the sum of distance for that
		//color, and when processing the colors on the current layer, just add to ans the sum of distance for the current
		//color. 
		
		//the thing that makes this problem tricky is the way you update the sum of distances for each color. 
		//notice that the naive solution has a O(NC) runtime, since every layer you have to update every color. 
		
		//the solution is to lazily update the color, only updating when necessary. You can do this by only updating
		//colors when they appear on the layer, when doing layer transitions, and when meeting a color when processing
		//a layer, remembering the last layer you updated this color on, and adding the difference accordingly. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[][] nums = new int[n][m];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < m; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		long ans = 0;
		//top to bottom
		HashMap<Integer, Long> cnt = new HashMap<>();
		HashMap<Integer, Long> sum = new HashMap<>();
		HashMap<Integer, Long> last = new HashMap<>();
		for(int i = 0; i < n; i++) {
			HashMap<Integer, Long> upd = new HashMap<>();
			for(int j = 0; j < m; j++) {
				upd.put(nums[i][j], (long) (upd.getOrDefault(nums[i][j], 0L) + 1));
				if(!last.containsKey(nums[i][j])) {
					last.put(nums[i][j], (long) i);
				}
				if(last.containsKey(nums[i][j]) && last.get(nums[i][j]) != i) {
					sum.put(nums[i][j], sum.getOrDefault(nums[i][j], 0L) + cnt.get(nums[i][j]) * (i - last.get(nums[i][j])));
					last.put(nums[i][j], (long) i);
				}
				if(sum.containsKey(nums[i][j])) {
					ans += sum.get(nums[i][j]);
				}
			}
			for(int k : upd.keySet()) {
				cnt.put(k, cnt.getOrDefault(k, 0L) + upd.get(k));
				sum.put(k, sum.getOrDefault(k, 0L) + cnt.get(k));
				last.put(k, (long) i + 1);
			}
		}
		//left to right
		cnt = new HashMap<>();
		sum = new HashMap<>();
		last = new HashMap<>();
		for(int i = 0; i < m; i++) {
			HashMap<Integer, Long> upd = new HashMap<>();
			for(int j = 0; j < n; j++) {
				upd.put(nums[j][i], upd.getOrDefault(nums[j][i], 0L) + 1);
				if(!last.containsKey(nums[j][i])) {
					last.put(nums[j][i], (long) i);
				}
				if(last.containsKey(nums[j][i]) && last.get(nums[j][i]) != i) {
					sum.put(nums[j][i], sum.getOrDefault(nums[j][i], 0L) + cnt.get(nums[j][i]) * (i - last.get(nums[j][i])));
					last.put(nums[j][i], (long) i);
				}
				if(sum.containsKey(nums[j][i])) {
					ans += sum.get(nums[j][i]);
				}
			}
			for(int k : upd.keySet()) {
				cnt.put(k, cnt.getOrDefault(k, 0L) + upd.get(k));
				sum.put(k, sum.getOrDefault(k, 0L) + cnt.get(k));
				last.put(k, (long) i + 1);
			}
			
		}
		System.out.println(ans);
	}
}
