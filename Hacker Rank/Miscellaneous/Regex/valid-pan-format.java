import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
   
  
    // https://www.hackerrank.com/challenges/valid-pan-format
    private static boolean isValidPAN(String s) {
     char[] char_array=s.toCharArray();
		 for (int i = 0; i < 5; i++) {
			if(Character.isLetter(char_array[i])==false || Character.isUpperCase(char_array[i])==false)
				return false;
		 }
		 for (int i =5 ; i < 9; i++) {
	         if(Character.isDigit(char_array[i])==false) return false;
		 }
		 if(Character.isLetter(char_array[9])==false || Character.isUpperCase(char_array[9])==false) return false;
	     return true;
    }
  
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        try {
            int i = Integer.parseInt(br.readLine());
            for (int j = 0; j < i; j++) {
                String s = br.readLine();
                System.out.println(isValidPAN(s) ? "YES" : "NO");
            }
        } catch (IOException e) {
            e.printStackTrace();
        } 
    }
}

