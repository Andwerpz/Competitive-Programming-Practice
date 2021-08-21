//package asyaandkittens;

import java.util.*;
import java.io.*;

public class asyaandkittens {
	public static void main(String[] args) throws IOException {
		
		//1131F
		
		//all you have to do is combine the kittens that are adjacent into sets. When combining two sets together, always add the smaller set to the bigger set. We can do this
		//since when adding sets, you always are at least doubling the size of the set that you are adding. This means that any given value will undergo a maximum of 
		//log(n) moves through sets, which gives us a final complexity of n * log(n).
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> stringIndex = new HashMap<Integer, Integer>();
		HashMap<Integer, HashSet<Integer>> groups = new HashMap<Integer, HashSet<Integer>>();
		ArrayList<StringBuilder> s = new ArrayList<StringBuilder>();
		int pointer = 0;
		for(int i = 0; i < n - 1; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			if(!dict.containsKey(a) && !dict.containsKey(b)) {
				dict.put(a, pointer);
				dict.put(b, pointer);
				HashSet<Integer> newSet = new HashSet<Integer>();
				newSet.add(a);
				newSet.add(b);
				groups.put(pointer, newSet);
				stringIndex.put(pointer, s.size());
				pointer ++;
				StringBuilder newString = new StringBuilder();
				newString.append(a).append(" ").append(b).append(" ");
				s.add(newString);
			}
			else if(!dict.containsKey(a)) {
				int group = dict.get(b);
				dict.put(a, group);
				groups.get(group).add(a);
				int index = stringIndex.get(group);
				s.get(index).append(a).append(" ");
			}
			else if(!dict.containsKey(b)) {
				int group = dict.get(a);
				dict.put(b, group);
				groups.get(group).add(b);
				int index = stringIndex.get(group);
				s.get(index).append(b).append(" ");
			}
			else {
				int groupA = dict.get(a);
				int groupB = dict.get(b);
				int indexA = stringIndex.get(groupA);
				int indexB = stringIndex.get(groupB);
				if(groups.get(groupA).size() > groups.get(groupB).size()) {
					for(int j : groups.get(groupB)) {
						dict.put(j, groupA);
					}
					groups.get(groupA).addAll(groups.get(groupB));
					s.get(indexA).append(s.get(indexB));
				}
				else {
					for(int j : groups.get(groupA)) {
						dict.put(j, groupB);
					}
					groups.get(groupB).addAll(groups.get(groupA));
					s.get(indexB).append(s.get(indexA));
				}
			}
//			System.out.println(dict);
//			System.out.println(groups);
		}
		System.out.println(s.get(stringIndex.get(dict.get(1))));
	}
}
