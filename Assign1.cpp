//Rajat Walia
//Assignment 1
//Feb. 25, 2019

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {


    //counter for each nucleotide and bigram
    double a=0, c=0, t=0, g=0;
    double aa=0, ac=0, at=0, ag=0, ca=0, cc=0, ct=0, cg=0, ta=0, tc=0, tt=0, tg=0, ga=0, gc=0, gt=0, gg=0;

    //counters for statistics calculation
    double line_count = 0;
    double line_sum_length = 0;
    double line_sum_length_sq = 0;
    double sum_nuc = 0;
    double sum_bigram = 0;
    double line_sum_curr = 0;

    //temp variables to contain read in nucleotides
    char nuc1, nuc2;

    //input file stream
    ifstream reader;
    //output file stream
    ofstream writer;




    //loop to process additional files
    char user_input = 'y';
    string file_name = argv[1];

    //while the user sitll wishes to process additional file, continue
    while(user_input == 'y') {

        //counter for each nucleotide and bigram
        a=0, c=0, t=0, g=0;
        aa=0, ac=0, at=0, ag=0, ca=0, cc=0, ct=0, cg=0, ta=0, tc=0, tt=0, tg=0, ga=0, gc=0, gt=0, gg=0;

        //counters for statistics calculation
         line_count = 0;
         line_sum_length = 0;
         line_sum_length_sq = 0;
         sum_nuc = 0;
         sum_bigram = 0;
         line_sum_curr = 0;

        //taking in file name from command line arguement
        cout << "The file path entered is: " << file_name << "\n";
        //dnatest.txt is the local testing file

        reader.open(file_name);

        //check if file stream opened successfully
        if (reader.fail()) {
          cout << "ERROR: file not opened. Exiting" << endl;
          return 1;
       }

       /*
       * Loop to read in each character, checking for correct nucleotides, updating counter variables for both nucleotides and bigrams
       * In order to optimize file reading, single loop to calculate and track mean and variance measures without multiple reads of file
       */

        while(!reader.eof()) {

            //read in new characters one at a time
            reader.read(&nuc1, 1);
            reader.read(&nuc2, 1);
            //cout << "#" << nuc1 << "##" << " and " << "%" << nuc2 << "%%" << endl;


            //change case for uniformity
            nuc1 = tolower(nuc1);
            nuc2 = tolower(nuc2);

            //check if either is the end of a line
            //becaause of complications on windows the \r checks are needed
            if(nuc1 == '\r' || nuc2 == '\n' || nuc1 == '\n') {
                line_count++;
                //required for variance calculation
                line_sum_length_sq += line_sum_curr*line_sum_curr;
                line_sum_curr = 0;
                continue;
            } else if(nuc2 == '\r') { //for lines with an odd number of chars
                sum_nuc++;
                reader.read(&nuc2, 1); //discard the new line after \r
                switch(nuc1) {
                    case 'a':
                        a++;
                        break;
                    case 'c':
                        c++;
                        break;
                    case 't':
                        t++;
                        break;
                    case 'g':
                        g++;
                        break;
                    default:
                        cout << "ERROR: No matching nucleotide found.(1) Exiting. " << endl;
                        return 1;
                        break;
                }
                line_count++;
                line_sum_length_sq += line_sum_curr*line_sum_curr;
                line_sum_curr = 0;
                continue;
            }

            //check for illegal characters - redundant in the end
            //necesary for debugging
            if(!isalpha(nuc1) || !isalpha(nuc2)) {
                cout << "ERROR: There is an illegal character in this DNA. Exiting. " << endl;
                cout << "##" << nuc1 << "##" << "%%" << nuc2 << "%%";
                return 1;
            }

            //count nucleotides and bigrams
            //given that both chars are legal nucleotides
            line_sum_length += 2;
            line_sum_curr += 2;
            sum_nuc += 2;
            sum_bigram++;
            switch(nuc1) {
                case 'a':
                a++;
                switch(nuc2) {
                    case 'a':
                        aa++;
                        a++;
                        break;
                    case 'c':
                        ac++;
                        c++;
                        break;
                    case 't':
                        at++;
                        t++;
                        break;
                    case 'g':
                        ag++;
                        g++;
                        break;
                    default:
                        cout << "ERROR: No matching bigram found.(1) Exiting. " << endl;
                        return 1;
                        break;
                }
                break;

                case 'c':
                c++;
                switch(nuc2) {
                    case 'a':
                        ca++;
                        a++;
                        break;
                    case 'c':
                        cc++;
                        c++;
                        break;
                    case 't':
                        ct++;
                        t++;
                        break;
                    case 'g':
                        cg++;
                        g++;
                        break;
                    default:
                        cout << "ERROR: No matching bigram found.(2) Exiting. " << endl;
                        return 1;
                        break;
                }
                break;

                case 't':
                    t++;
                switch(nuc2) {
                    case 'a':
                        ta++;
                        a++;
                        break;
                    case 'c':
                        tc++;
                        c++;
                        break;
                    case 't':
                        tt++;
                        t++;
                        break;
                    case 'g':
                        tg++;
                        g++;
                        break;
                    default:
                        cout << "ERROR: No matching bigram found.(3) Exiting. " << endl;
                        return 1;
                        break;
                }
                break;

                case 'g':
                    g++;
                switch(nuc2) {
                    case 'a':
                        ga++;
                        a++;
                        break;
                    case 'c':
                        gc++;
                        c++;
                        break;
                    case 't':
                        gt++;
                        t++;
                        break;
                    case 'g':
                        gg++;
                        g++;
                        break;
                    default:
                        cout << "ERROR: No matching bigram found.(4) Exiting. " << endl;
                        return 1;
                        break;
                }
                break;

                default:
                    cout << "ERROR: No matching nucleotide found.(2) Exiting. " << endl;
                    return 1;
                    break;
            }

        } //END OF WHILE LOOP  FOR READING CHARS

        //calculating variance and SD
        double line_var = (line_sum_length_sq - (line_sum_length*line_sum_length)/line_count)/(line_count - 1);
        double line_sd = sqrt(line_var);

        //calculating average line length
        double line_mean = line_sum_length/line_count;


        //calculating probabilities for nucleotides
        double prob_a = a/sum_nuc;
        double prob_c = c/sum_nuc;
        double prob_t = g/sum_nuc;
        double prob_g = t/sum_nuc;

        //calculating probabilities for bigrams
        double prob_aa = aa/sum_bigram;
        double prob_ac = ac/sum_bigram;
        double prob_at = at/sum_bigram;
        double prob_ag = ag/sum_bigram;

        double prob_ca = ca/sum_bigram;
        double prob_cc = cc/sum_bigram;
        double prob_ct = ct/sum_bigram;
        double prob_cg = cg/sum_bigram;

        double prob_ta = ta/sum_bigram;
        double prob_tc = tc/sum_bigram;
        double prob_tt = tt/sum_bigram;
        double prob_tg = tg/sum_bigram;

        double prob_ga = ga/sum_bigram;
        double prob_gc = gc/sum_bigram;
        double prob_gt = gt/sum_bigram;
        double prob_gg = gg/sum_bigram;

        reader.close();

        //finished reading input file and calculations
        //opening output file to report results

        writer.open("RajatWalia.txt", ios :: out | ios :: app);

        //writing answers into output file
        writer << "Rajat Walia : 2330164" << endl;
        writer << "CPSC350 - 1 : German" << endl;

        writer << "Probabilities for nucleotides(a-c-g-t): " << prob_a << " - " << prob_c << " - " << prob_t << " - " << prob_g << endl;
        writer << "Probabilities for bigrams(aa-ac-at-ag): " << prob_aa << " - " << prob_ac << " - " << prob_at << " - " << prob_ag << endl;
        writer << "Probabilities for bigrams(ca-cc-ct-cg): " << prob_ca << " - " << prob_cc << " - " << prob_ct << " - " << prob_cg << endl;
        writer << "Probabilities for bigrams(ta-tc-tt-tg): " << prob_ta << " - " << prob_tc << " - " << prob_tt << " - " << prob_tg << endl;
        writer << "Probabilities for bigrams(ga-gc-gt-gg): " << prob_ga << " - " << prob_gc << " - " << prob_gt << " - " << prob_gg << endl;

        writer << "Average line length: " << line_mean << endl;
        writer << "Variance in line length " << line_var << endl;
        writer << "Standard Deviation in line length " << line_sd << endl;


        //generating 1000 new DNA strings
        double rand1 = 0;
        double rand2 = 0;
        double gaussian_distro = 0;

        for(int i = 0; i < 1000; ++i) {
            int rand_length = 0;

            while(rand_length < 1) {
                rand1 = ((double) rand() / (RAND_MAX));
                rand2 = ((double) rand() / (RAND_MAX));
                //generating gaussian distribution and new line length
                gaussian_distro = sqrt((-2) * log(rand1)) * cos(2 * M_PI * rand2);

                rand_length = line_sd*gaussian_distro + line_mean;
            }

            double rand_char = 0;

            for(int j = 0; j < rand_length; ++j) {
                //random value to determine new nucleotides
                rand_char = ((double) rand() / (RAND_MAX));
                if(rand_char < prob_a) {
                    writer << 'A';
                } else if(rand_char < (prob_a + prob_c)) {
                    writer << 'C';
                }else if (rand_char < (prob_a + prob_c + prob_t)) {
                    writer << 'T';
                } else {
                    writer << 'G';
                }
            }
            writer << "\n";
        }

        writer.close();

        cout << "Finished processing " << file_name << endl;

        //ask for further input from user to process additional files
        cout << "Enter y if you wish to process any additional files, to close program enter n: ";
        cin >> user_input;
        if(user_input == 'y') {
            cout << "\nPlease enter another file path: ";
            cin >> file_name;
        }
    }   //FINAL LOOP



    cout << "FIN" << endl;
    return 0;
}
