//package arraypartition;

import java.util.*;
import java.io.*;

public class arraypartitionver1 {
	
	static ArrayList<ArrayList<Integer>> tree;	//handle range minimum queries
	
	public static int getMinimum(int l, int r) {
		//System.out.println("SEARCH");
		int index = l;
		int increment = 1;
		int layer = 0;
		int ans = Integer.MAX_VALUE;
		for(int i = l; i <= r; i += 0) {
			while((index / 2) * increment * 2 > l && ((index / 2) * increment + increment) * 2 < r) {
				index /= 2;
				increment *= 2;
				layer ++;
			}
			while(index * increment < l || index * increment + increment - 1 > r) {
				if(increment == 0) {
					//System.out.println("YES");
					return ans;
				}
				if(index * increment < l) {
					index *= 2;
					index ++;
				}
				else {
					index *= 2;
				}
				increment /= 2;
				layer --;
			}
			int curAns = tree.get(layer).get(index);
			ans = Math.min(curAns, ans);
			i += increment;
			index ++;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1454F
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int treeSize = (int) (Math.pow(2, Math.ceil(Math.log(n) / Math.log(2))));
			tree = new ArrayList<ArrayList<Integer>>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			int[] pfx = new int[n];	//pfx sfx maximum
			int[] sfx = new int[n];
			for(int i = 0; i < treeSize; i++) {
				int next = Integer.MAX_VALUE;
				if(i < n) {
					next = Integer.parseInt(st.nextToken());
					nums[i] = next;
				}
				int layer = 0;
				while(true) {
					if(layer == tree.size()) {
						tree.add(new ArrayList<Integer>());
					}
					if(layer == 0) {
						tree.get(0).add(next);
					}
					else {
						int size = tree.get(layer - 1).size();
						int a = tree.get(layer - 1).get(size - 1);
						int b = tree.get(layer - 1).get(size - 2);
						tree.get(layer).add(Math.min(a, b));
					}
					if(tree.get(layer).size() % 2 == 0) {
						layer ++;
					}
					else {
						break;
					}
				}
			}
			//System.out.println(tree);
			for(int i = 0; i < n; i++) {
				if(i == 0) {
					pfx[i] = nums[i];
				}
				else {
					pfx[i] = Math.max(pfx[i - 1], nums[i]);
				}
			}
			for(int i = n - 1; i >= 0; i--) {
				if(i == n - 1) {
					sfx[i] = nums[i];
				}
				else {
					sfx[i] = Math.max(sfx[i + 1], nums[i]);
				}
			}
			boolean isValid = false;
			outer:
			for(int i = 0; i < n - 2; i++) {
				int curVal = pfx[i];
				//System.out.println(curVal);
				int low = i + 1;
				int high = n - 2;
				int mid = low + (high - low) / 2;
				int	lowLim = n;
				int highLim = 0;
				boolean foundAns = false;
				while(low <= high) {
					int nextMin = getMinimum(i + 1, mid);
					//System.out.println(nextMin + " " + mid);
					if(nextMin <= curVal) {
						high = mid - 1;
					}
					else {
						low = mid + 1;
					}
					if(nextMin == curVal) {
						foundAns = true;
						lowLim = Math.min(lowLim, mid);
					}
					mid = low + (high - low) / 2;
				}
				if(foundAns) {
					//System.out.println("LOW: " + lowLim);
					low = lowLim;
					high = n - 2;
					mid = low + (high - low) / 2;
					foundAns = false;
					while(low <= high) {
						int nextMin = getMinimum(i + 1, mid);
						if(nextMin < curVal) {
							high = mid - 1;
						}
						else {
							low = mid + 1;
						}
						if(nextMin == curVal) {
							foundAns = true;
							highLim = Math.max(highLim, mid);
						}
						mid = low + (high - low) / 2;
					}
					if(foundAns) {
						//System.out.println("HIGH: " + highLim);
						low = lowLim + 1;
						high = highLim + 1;
						mid = low + (high - low) / 2;
						foundAns = false;
						while(low <= high) {
							int nextMax = sfx[mid];
							//System.out.println(nextMax + " " + mid);
							if(nextMax < curVal) {
								high = mid - 1;
							}
							else {
								low = mid + 1;
							}
							if(nextMax == curVal) {
								foundAns = true;
								highLim = mid;
								break;
							}
							mid = low + (high - low) / 2;
						}
						if(foundAns) {
							isValid = true;
							//System.out.println(lowLim + " " + highLim);
							fout.append("YES\n");
							fout.append(i + 1).append(" ").append(Math.abs(highLim - (i + 1))).append(" ").append(n - (highLim)).append("\n");
							break outer;
						}
					}
				}
			}
			if(!isValid) {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
