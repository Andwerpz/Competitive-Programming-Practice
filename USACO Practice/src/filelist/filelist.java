//package filelist;

import java.util.*;
import java.io.*;

public class filelist {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		String input = fin.readLine();
		ArrayList<String> s = new ArrayList<String>();
		s.add("");
		boolean isValid = true;
		for(int i = 0; i < input.length(); i++) {
			if(input.charAt(i) == '.') {
				s.add("");
			}
			else {
				s.set(s.size() - 1, s.get(s.size() - 1) + input.charAt(i));
			}
			if(s.get(s.size() - 1).length() > 11) {
				isValid = false;
				break;
			}
		}
		int n = s.size();
		
		for(int i = 0; i < n; i++) {
			if(i == 0) {
				if(s.get(i).length() > 8 || s.get(i).length() == 0) {
					isValid = false;
					break;
				}
			}
			else if(i == n - 1) {
				if(s.get(i).length() > 3 || s.get(i).length() == 0) {
					isValid = false;
				}
			}
			else {
				if(s.get(i).length() > 11 || s.get(i).length() < 2) {
					isValid = false;
				}
			}
		}
		if(s.size() < 2) {
			isValid = false;
		}
		if(isValid) {
			StringBuilder fout = new StringBuilder();
			for(int i = 0; i < n; i++) {
				if(i == 0) {
					fout.append(s.get(i)).append(".");
				}
				else if(i == n - 1) {
					fout.append(s.get(i)).append("\n");
				}
				else {
					if(s.get(i).length() <= 3) {
						fout.append(s.get(i).substring(0, 1)).append("\n").append(s.get(i).substring(1)).append(".");
					}
					else {
						fout.append(s.get(i).substring(0, 3)).append("\n").append(s.get(i).substring(3)).append(".");
					}
				}
			}
			System.out.println("YES");
			System.out.print(fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
