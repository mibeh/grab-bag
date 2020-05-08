// This program can be used to encrypt and decrypt a message using the
// ADFGVX cipher.

import java.io.*;
import java.util.*;

public class ADFGVX{

    public static String[] ciphertext;
    public static String[] plaintext;
    public static String letterLookup = "ADFGVX";
    public static char[][] grid;
    public static int[] permutation;

    public static void main(String[] args) throws IOException {
 
        grid = new char[6][6];
        int mode;
        int numMessages;
        int fullRows, extraLetters; 
        String keyword;
        

        Scanner sc =  new Scanner(System.in);

        for(int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                grid[i][j] = sc.next().charAt(0);
            }
        }

        keyword = sc.next().toString();
      
        // Find keyword permeutation for columns
        permutation = permArray(keyword);
      
        numMessages = sc.nextInt();
      
        ciphertext = new String[numMessages];
        plaintext = new String[numMessages];
      
        for(int i = 0; i < numMessages; i++){

            mode = sc.nextInt();
          
            if(mode == 1){
                plaintext[i] = sc.next().toString();
                System.out.println(encrypt(plaintext[i]));
            }
            else if(mode == 2){
                ciphertext[i] = sc.next().toString();
                
                // Number of fullRows
                fullRows = ciphertext[i].length() / keyword.length();
              
                // Number of extra letters 
                extraLetters = ciphertext[i].length() % keyword.length();
                
                // Print out decrypted text
                System.out.println(decrypt(ciphertext[i], fullRows, extraLetters, keyword));
            }
        }
    } 
    // Alphabetize the keyword and get the int array for permutations
    public static int[] permArray(String keyword){
        // Keyword length
        int keyL = keyword.length();
        
        // Permutation
        int[] perm = new int[keyL];     
        
        // Create array objects to hold letters and their index
        permFinder[] sorted = new permFinder[keyL];
        
        for(int i = 0; i < keyL; i++)
            sorted[i] = new permFinder(keyword.charAt(i), i);
        
        // Sort letters with their indexes
        Arrays.sort(sorted);
        
        // Assign new sorted indexes to new int array
        for(int i = 0; i < keyL; i++)
            perm[i] = sorted[i].index;
        
        return perm;
    }

    public static String encrypt(String plaintext){
      
      String substituted = "";
      String encrypted = "";
      
      // Substituion phase
      for(int k = 0; k < plaintext.length(); k++){  
          
          for(int i = 0; i < 6; i++){
            
              // Finds unencrypted char in key grid and substitues the cipher chars
              // Index = Ciphertext Char
                  // 0 = A
                  // 1 = D
                  // 2 = F
                  // 3 = G
                  // 4 = V
                  // 5 = X
              for(int j = 0; j < 6; j++){

                  if(grid[i][j] == plaintext.charAt(k)){
                    substituted += letterLookup.charAt(i);
                    substituted += letterLookup.charAt(j);
                  }

              }
          }
      }
      
      // Transposition Phase
      for (int i = 0;i < permutation.length; i++) 
        for (int j=permutation[i]; j < substituted.length(); j+= permutation.length)
          encrypted += substituted.charAt(j);
        
      return encrypted;
    }

    public static String decrypt(String ciphertext, int fullRows, int extraLetters, String keyword){
        // Vars
        String decrypted = "";
        char[] partial = new char[ciphertext.length()];
        int rowValue = 0;
      
        // rowValue
        if(extraLetters > 0){
          rowValue = fullRows++;
        }
   
        
        return decrypted;
    }
}

// Used for finding permutation of keyword
class permFinder implements Comparable<permFinder> {

  public char letter;
  public int index;

  public permFinder(char l, int i) {
    letter = l;
    index  = i;
  }

  public int compareTo(permFinder other) {
    // Check for double letters
    if (this.letter != other.letter)
      return this.letter - other.letter;
    return this.index - other.index;
  }
 
}
