#include "analysisTools.h"
/*
ClassImp(recoSettings);
ClassImp(recoData);
ClassImp(cutParameter);
ClassImp(ARA02_cutValues);
*/
using namespace std;

int getRunType(string STATION, int runNum){

   int type;

   if ( STATION == "ARA02" ) {
      if ( runNum >= 2275 && runNum <= 3463) {
         type = 1;
      } else if ( runNum >= 120 && runNum <= 2274 ) {
         type = 2;
      } else if ( runNum >= 3465 && runNum <= 4027 ){
         type = 3;
      } else if ( ( runNum >= 4029 && runNum <= 6481) || ( runNum >= 3 && runNum <= 60) || ( runNum >= 8100 && runNum <= 8246) ){
         type = 4;
      } else if ( (runNum >= 6500 && runNum <= 8097) || runNum == 0 ){
         type = 5;
      } else {
         type = 0;
      }
   } else if ( STATION == "ARA03" ) {
      if ( runNum >= 1449 && runNum <= 3061 ) {
         type = 1;
      } else if ( runNum >= 470 && runNum <= 1448 ) {
         type = 2;
      } else if ( (runNum >= 3063 && runNum <=6004) || ( runNum >= 7658 && runNum <= 7808 ) ){
         type = 3;
      } else if ( runNum >= 6005 && runNum <= 7653 ){
         type = 4;
      } else {
         type = 0;
      }
   } else {
      type = 0;
   }

   return type;

}

cutParameter::cutParameter() {  }
cutParameter::~cutParameter() { /*default destructor*/ }

ARA02_cutValues::ARA02_cutValues(){ initialize(); }
ARA02_cutValues::~ARA02_cutValues(){ /* default destructor */ }

void ARA02_cutValues::initialize(){


   setValue(cwImpCut[0], 0.29936375,0.00071682,-0.00071682);
   setValue(cwImpCut[1], 0.32188931,0.00097344,-0.00097344);
   setValue(cwImpCut[2], 0.2955359,0.00070074,-0.00070074);
   setValue(cwImpCut[3], 0.30005502,0.00111114,-0.00111114);
   setValue(cwImpCut[4], 0.29206096,0.0019572,-0.0019572);

//Cut values from crest factor n-chan
/*
   setValue(snrCut_inBand[0], 8.97, 0.018104, -0.017988);
   setValue(snrCut_inBand[1], 9.116000, 0.017207, -0.017098);
   setValue(snrCut_inBand[2], 8.640000, 0.093084, -0.089897);
   setValue(snrCut_inBand[3], 9.360000, 0.022266, -0.022081);
   setValue(snrCut_inBand[4], 9.480000, 0.033537, -0.033128);

   setValue(coherenceCut_inBand[0], 0.108971, 0.000276, -0.000271);
   setValue(coherenceCut_inBand[1], 0.111546, 0.000198, -0.000195);
   setValue(coherenceCut_inBand[2], 0.106706, 0.000192, -0.000189);
   setValue(coherenceCut_inBand[3], 0.099455, 0.000143, -0.000141);
   setValue(coherenceCut_inBand[4], 0.098104, 0.000146, -0.000144);

   setValue(snrCut_outOfBand[0],9.000000, 0.033720, -0.033304);
   setValue(snrCut_outOfBand[1],9.128000, 0.021496, -0.021326);
   setValue(snrCut_outOfBand[2],8.704000, 0.096490, -0.093141);
   setValue(snrCut_outOfBand[3],9.524000, 0.033422, -0.033023);
   setValue(snrCut_outOfBand[4],10.028000, 0.184248, -0.174582);

   setValue(coherenceCut_outOfBand[0],0.103402, 0.000165, -0.000162);
   setValue(coherenceCut_outOfBand[1],0.105563, 0.000149, -0.000147);
   setValue(coherenceCut_outOfBand[2],0.101873, 0.000134, -0.000132);
   setValue(coherenceCut_outOfBand[3],0.094399, 0.000217, -0.000212);
   setValue(coherenceCut_outOfBand[4],0.092622, 0.000142, -0.000140);
*/

   //Cut values from sliding V^2 SNR n-chan
   setValue(snrCut_inBand[0], 12.935000, 0.552648, -0.509019);
   setValue(snrCut_inBand[1], 13.365000, 0.051088, -0.050650);
   setValue(snrCut_inBand[2], 12.230000, 0.053964, -0.053508);
   setValue(snrCut_inBand[3], 12.535000, 0.039439, -0.039147);
   setValue(snrCut_inBand[4], 12.725000, 0.041504, -0.041191);

   setValue(coherenceCut_inBand[0], 0.108061, 0.000236, -0.000231);
   setValue(coherenceCut_inBand[1], 0.109367, 0.000201, -0.000198);
   setValue(coherenceCut_inBand[2], 0.108527, 0.000255, -0.000250);
   setValue(coherenceCut_inBand[3], 0.099249, 0.000142, -0.000140);
   setValue(coherenceCut_inBand[4], 0.097097, 0.000132, -0.000131);

   setValue(snrCut_outOfBand[0],11.815000, 0.048386, -0.047920);
   setValue(snrCut_outOfBand[1],13.325000, 0.042806, -0.042496);
   setValue(snrCut_outOfBand[2],12.185000, 0.057194, -0.056679);
   setValue(snrCut_outOfBand[3],13.180000, 0.052173, -0.051708);
   setValue(snrCut_outOfBand[4],12.860000, 0.041406, -0.041101);

   setValue(coherenceCut_outOfBand[0],0.103742, 0.000151, -0.000149);
   setValue(coherenceCut_outOfBand[1],0.107307, 0.000144, -0.000142);
   setValue(coherenceCut_outOfBand[2],0.103737, 0.000132, -0.000130);
   setValue(coherenceCut_outOfBand[3],0.094770, 0.000120, -0.000119);
   setValue(coherenceCut_outOfBand[4],0.095079, 0.000324, -0.000315);

   //setValue(impCut, 0.25563478, 0.00124038, -0.00124038);
   setValue(impCut, 0.28108427, 0.00160186, -0.00160186);
/*
   setValue(zenMin[0],0.5409,	-0.001924625,	0.001924625); // plus: cut region is larger minus: cut regin is smaller
   setValue(zenMin[1],-31.4,	-0.030723404,	0.030723404);
   setValue(zenMin[2],-27.78,	-0.0405,	0.0405);
   setValue(zenMin[3],24.07,	-0.005442857,	0.005442857);

   setValue(zenMax[0],10.99,	0.01,	-0.01);
   setValue(zenMax[1],-14.26,	0.01,	-0.01);
   setValue(zenMax[2],-14.22,	0.0285,	-0.0285);
   setValue(zenMax[3],31.45,	0.050333333,	-0.050333333);

   setValue(aziMin[0],54.96,	-0.01,	0.01);
   setValue(aziMin[1],324.05,	-0.003317073,	0.003317073);
   setValue(aziMin[2],50.8,	-0.041156863,	0.041156863);
   setValue(aziMin[3],67.3,	-0.0022315,	0.0022315);

   setValue(aziMax[0],66.74,	0.0001,	-0.0001);
   setValue(aziMax[1],341.01,	0.027090909,	-0.027090909);
   setValue(aziMax[2],58.32,	0.015909091,	-0.015909091);
   setValue(aziMax[3],75.25,	0.010268085,	-0.010268085);
*/

   setValue(zenMin[0], -32.445122,  -0.279150, 0.279150); // plus: cut region is larger minus: cut regin is smaller
   setValue(zenMin[1], -0.5000384756620608, -0.049698, 0.049698);
   setValue(zenMin[2], 26.676257582375015,  -0.014895, 0.014895);

   setValue(zenMax[0], -15.09135433852994, 0.644769, -0.644769);
   setValue(zenMax[1], 11.197893462051383, 0.005116, -0.005116);
   setValue(zenMax[2], 36.74904979886475, 0.002851, -0.002851);

   setValue(aziMin[0], 329.1813651101607, -0.011490, 0.011490);
   setValue(aziMin[1], 55.31723520228566, -0.000069, 0.000069);
   setValue(aziMin[2], 330.64429515858507,  -0.009783, 0.009783);

   setValue(aziMax[0], 341.4794531938459, 0.287608, -0.287608);
   setValue(aziMax[1], 67.22731842523841, 0.018698, -0.018698);
   setValue(aziMax[2], 340.74104652018354, 0.739811, -0.739811);
/*
   setValue(surfaceCut_constantN, 35.648,	-0.693,	0.693); // plus: cut region is larger, minus: cut region is smaller
   setValue(surfaceCut_iterReco, 36.77852,	-0.588241,	0.588241);
*/
   setValue(surfaceCut_constantN, 35.95705,	-0.749395,	0.749395); // plus: cut region is larger, minus: cut region is smaller
   setValue(surfaceCut_iterReco, 31.62731,	-1.217763,	1.217763);

}

void ARA02_cutValues::setValue(cutParameter& param, double _val, double _plus, double _minus){

   param.val = _val;
   param.plus = _plus;
   param.minus = _minus;

}


bool isCW_coincidence(bool &isVpolCW, bool &isHpolCW, int &maxCountFreqBin_V, int &maxCountFreqBin_H, recoData *dummyData, int cwBinThres){

   vector<int> maxFreqBinVec_V;
   vector<int> maxFreqBinVec_H;
   vector<int> maxFreqBinVec;

   maxFreqBinVec_V.clear();
   maxFreqBinVec_H.clear();
   maxFreqBinVec.clear();

   for(int i=0; i<8; i++){
      //cout<<"ch: "<<i<<" maxFreqBin: "<<dummyData->maxFreqBin[i]<<" maxFreq: "<<dummyData->maxFreqBin[i] * dummyData->freqBinWidth_V<<" maxFreqPower: "<<dummyData->maxFreqPower[i]<<" ";
      maxFreqBinVec_V.push_back(dummyData->maxFreqBin[i]);
   }
   //cout<<endl;
   for(int i=8; i<16; i++){
      //cout<<"ch: "<<i<<" maxFreqBin: "<<dummyData->maxFreqBin[i]<<" maxFreq: "<<dummyData->maxFreqBin[i] * dummyData->freqBinWidth_H<<" maxFreqPower: "<<dummyData->maxFreqPower[i]<<" ";
      maxFreqBinVec_H.push_back(dummyData->maxFreqBin[i]);
   }
   //cout<<endl;
   //cout<<"maxCountFreq_V: "<<dummyData->maxCountFreq_V<<" maxCountFreq_H: "<<dummyData->maxCountFreq_H<<endl;

   int minBin  =  *min_element(maxFreqBinVec_V.begin(), maxFreqBinVec_V.end());
   int maxBin  =  *max_element(maxFreqBinVec_V.begin(), maxFreqBinVec_V.end());
   int len = maxBin - minBin + 1;
   int* freqCount_V = new int [len];
   std::fill(&freqCount_V[0], &freqCount_V[len], 0);

   for(int i=0; i<8; i++) freqCount_V[dummyData->maxFreqBin[i]-minBin] += 1;

   for(int i=0; i<len; i++){
      if(freqCount_V[i] >= cwBinThres) { isVpolCW = true; maxCountFreqBin_V = minBin+i; }
   }

   if(!isVpolCW){
      if (freqCount_V[0] >= cwBinThres-1){
         if (freqCount_V[1] >= cwBinThres-2 ) { isVpolCW = true; maxCountFreqBin_V = minBin+0; }
      } else if ( freqCount_V[len-1] >= cwBinThres-1){
         if (freqCount_V[len-2] >= cwBinThres-2 ) { isVpolCW = true; maxCountFreqBin_V = minBin+len-1; }
      }
   }
   if (!isVpolCW){
      for(int i=1; i<len-1; i++){
         if(freqCount_V[i]>=cwBinThres-1){
            if(freqCount_V[i-1] >= cwBinThres-2 || freqCount_V[i+1] >= cwBinThres-2){
               isVpolCW = true;
               maxCountFreqBin_V = minBin+i;
               break;
            }
         }
      }
   }


   minBin  =  *min_element(maxFreqBinVec_H.begin(), maxFreqBinVec_H.end());
   maxBin  =  *max_element(maxFreqBinVec_H.begin(), maxFreqBinVec_H.end());
   len = maxBin - minBin + 1;
   int* freqCount_H = new int [len];
   std::fill(&freqCount_H[0], &freqCount_H[len], 0);

   for(int i=8; i<16; i++) freqCount_H[dummyData->maxFreqBin[i]-minBin] += 1;

   for(int i=0; i<len; i++){
      if(freqCount_H[i] >= cwBinThres) { isHpolCW = true; maxCountFreqBin_H = minBin+i; }
   }

   if(!isHpolCW){
      if (freqCount_H[0] >= cwBinThres-1){
         if (freqCount_H[1] >= cwBinThres-2 ) { isHpolCW = true; maxCountFreqBin_H = minBin+0; }
      } else if ( freqCount_H[len-1] >= cwBinThres-1){
         if (freqCount_H[len-2] >= cwBinThres-2 ) { isHpolCW = true; maxCountFreqBin_H = minBin+len-1; }
      }
   }
   if (!isHpolCW){
      for(int i=1; i<len-1; i++){
         if(freqCount_H[i]>=cwBinThres-1){
            if(freqCount_H[i-1] >= cwBinThres-2 || freqCount_H[i+1] >= cwBinThres-2){
               isHpolCW = true;
               maxCountFreqBin_H = minBin+i;
               break;
            }
         }
      }
   }

   delete [] freqCount_V;
   delete [] freqCount_H;

   return (isVpolCW || isHpolCW);

}

bool isCW_freqWindow(bool &isVpolCW, bool &isHpolCW, bool isXpolCW, recoData *dummyData, double fftRes){

   bool isCW = false;

   double maxFreqArray[16];
   int maxFreqArrayPolType[16];
   int fIndex[16];
   double orderedArray[16];
   int orderedArrayPolType[16];

      for(int ch=0; ch<16; ch++){

         //maxFreqBinVec.push_back(dummyData->maxFreqBin[ch]);
         maxFreqArray[ch] = dummyData->maxFreqBin[ch] * (ch<8?dummyData->freqBinWidth_V:dummyData->freqBinWidth_H);
         if(ch<8) maxFreqArrayPolType[ch] = 0;//maxFreqArray_V[ch] =  dummyData->maxFreqBin[ch] * dummyData->freqBinWidth_V;
         else     maxFreqArrayPolType[ch] = 1;//maxFreqArray_H[ch] =  dummyData->maxFreqBin[ch] * dummyData->freqBinWidth_H;

      }



      TMath::Sort(16, maxFreqArray, fIndex, kFALSE);
      //TMath::Sort(8, maxFreqArray_V, fIndex_V, kFALSE);
      //TMath::Sort(8, maxFreqArray_H, fIndex_H, kFALSE);


      for(int ch=0; ch<16; ch++){

         orderedArray[ch] = maxFreqArray[fIndex[ch]];
         orderedArrayPolType[ch] = maxFreqArrayPolType[fIndex[ch]];
         //cout<<orderedArray[ch]<<",";

      }
      //cout<<endl;
/*
      for(int ch=0; ch<8; ch++){

         orderedArray[ch] =

      }
*/
      int cwCount=0;
      int cwCount_V, cwCount_H, cwCount_X;
      cwCount_V = cwCount_H = cwCount_X = 0;

      for(int i=0; i<16; i++){
         for(int j=i+1; j<16; j++){

            //cout<<"i: "<<i<<" j: "<<j<<endl;
            double fftResGap;
            if(orderedArrayPolType[i]+orderedArrayPolType[j] == 0){ //2 Vpol
               //fftRes = 2. * dummyData->freqBinWidth_V;
               int vResBin = int(fftRes / dummyData->freqBinWidth_V)+1;
               fftResGap = dummyData->freqBinWidth_V * (double)vResBin;
            }
            else if(orderedArrayPolType[i]+orderedArrayPolType[j] == 2){ //2H
               //fftRes = dummyData->freqBinWidth_V + dummyData->freqBinWidth_H;
               int hResBin = int(fftRes / dummyData->freqBinWidth_H)+1;
               fftResGap = dummyData->freqBinWidth_H * (double)hResBin;
            }
            else{ //1V + 1H
              //fftRes = 2. * dummyData->freqBinWidth_H;
              //xResBin = int(fftRes / (dummyData->freqBinWidth_V + dummyData->freqBinWidth_H));
              //fftResGap = (dummyData->freqBinWidth_V + dummyData->freqBinWidth_H) * (double)xResBin + (dummyData->freqBinWidth_V>dummyData->freqBinWidth_H?dummyData->freqBinWidth_V:dummyData->freqBinWidth_H);
              fftResGap = fftRes + (dummyData->freqBinWidth_V>dummyData->freqBinWidth_H?dummyData->freqBinWidth_V:dummyData->freqBinWidth_H);
            }

            //cout<<"poltype: "<<orderedArrayPolType[i]+orderedArrayPolType[j]<<" fftResGap: "<<fftResGap<<" orderedArray[i]: "<<orderedArray[i]<<" orderedArray[j]: "<<orderedArray[j]<<" diff: "<<orderedArray[j]-orderedArray[i]<<endl;
            //printf("fftResGap: %le diff: %le diff-fftResGap: %le\n", fftResGap, orderedArray[j]-orderedArray[i], orderedArray[j]-orderedArray[i]-fftResGap);
            if(orderedArray[i] > 1e-6 && orderedArray[j] > 1e-6){ //not zeros

            if( (orderedArray[j] - orderedArray[i]) < fftResGap+1e-6/*fftRes*/) {
               //cout<<"i: "<<i<<" j: "<<j<<" freq_i: "<<orderedArray[i]<<" freq_j: "<<orderedArray[j]<<endl;
               if(orderedArrayPolType[i]+orderedArrayPolType[j] == 0){ cwCount_V++; }
               else if (orderedArrayPolType[i]+orderedArrayPolType[j] == 2){ cwCount_H++; }
               else {cwCount_X++;}
               cwCount++;
               i = j;
            }

            }

         }
      }

      if(cwCount_V>=2) isVpolCW = true;
      if(cwCount_H>=2) isHpolCW = true;
      if(cwCount_X>=2) isXpolCW = true;
      if(cwCount>=2) isCW = true;//cout<<"CW EVENT!!!!!"<<endl;
      else isCW=false;//cout<<"NOT CW!!!!!"<<endl;

      return isCW;

}

bool isLowFreqDominance(int& lowFreqCount_V, int& lowFreqCount_H, recoData *dummyData, double highPassFreq, int lowFreqCountThres){

   lowFreqCount_V = lowFreqCount_H = 0;

   for(int i=0; i<8; i++){
      //cout<<"maxFreqBin: "<<dummyData->maxFreqBin[i]<<" maxFreq_V: "<<dummyData->maxFreqBin[i]   * dummyData->freqBinWidth_V<<endl;
      //cout<<"maxFreqBin: "<<dummyData->maxFreqBin[i+8]<<" maxFreq_H: "<<dummyData->maxFreqBin[i+8]   * dummyData->freqBinWidth_H<<endl;
      if( dummyData->maxFreqBin[i]   * dummyData->freqBinWidth_V < highPassFreq ) lowFreqCount_V += 1;
      if( dummyData->maxFreqBin[i+8] * dummyData->freqBinWidth_H < highPassFreq ) lowFreqCount_H += 1;
   }

   if(lowFreqCount_V >= lowFreqCountThres || lowFreqCount_H >= lowFreqCountThres) //lowFreqDominance = true;
      return true;
   else
      return false;

}

bool isThermal_boxCut(bool &inBand, recoSettings *settings, recoData *dummyData, Healpix_Onion onion, double snrCut_inBand, double coherenceCut_inBand, double snrCut_outOfBand, double coherenceCut_outOfBand){

      float r     = onion.getLayerRadius(dummyData->maxPixIdx2);
      float theta = onion.getPointing(dummyData->maxPixIdx2).theta * TMath::RadToDeg();
      float phi   = onion.getPointing(dummyData->maxPixIdx2).phi   * TMath::RadToDeg();

      float zen_bestHypo, azi_bestHypo;
      double coherence, snr;

      double snrCutValue, coherenceCutValue;

      bool passThermalCut;

      if(dummyData->maxPixCoherence > dummyData->maxPixCoherence2){

         zen_bestHypo = 90.f-dummyData->recoZen;
         azi_bestHypo = dummyData->recoAzi;
         coherence = dummyData->maxPixCoherence;

      } else {

         zen_bestHypo = 90.f-theta;
         azi_bestHypo = phi;
         coherence = dummyData->maxPixCoherence2;

      }

      if (zen_bestHypo < ZEN_BAND_MAX && zen_bestHypo > ZEN_BAND_MIN){
         snrCutValue = snrCut_inBand;
         coherenceCutValue = coherenceCut_inBand;
         inBand = true;
      }
      else {
         snrCutValue = snrCut_outOfBand;
         coherenceCutValue = coherenceCut_outOfBand;
         inBand = false;
       }

      if(string(settings->recoPolType)=="vpol"){ snr = dummyData->inWindowSNR_V; }
      else if(string(settings->recoPolType)=="hpol"){ snr = dummyData->inWindowSNR_H; }

      if( snr > snrCutValue || coherence > coherenceCutValue){
         passThermalCut = true;
      } else {
         passThermalCut = false;
      }

   return !passThermalCut;
}

bool isSurface(recoData *dummyData, double surfaceCut_1){

      if(90.f-dummyData->constantNZen < /*SURFACE_CUT*/surfaceCut_1){
         //passSurfaceCut = true;
         return false;
      } else {
         return true;
       }

}

bool isIterSurface(double &zenMaj, recoData *dummyData, Healpix_Onion onion, recoSettings *settings, double zenRange, double surfaceCut_2){

   int nAnt = (string(settings->recoPolType)=="both"?16:8);
   int numIter = nAnt - settings->nchnlCut + 1;
   int nLayer = settings->nLayer;
   vector<float> iterZenVec;
   iterZenVec.clear();

   int iterIndex[nLayer];
   float iterMaxPixCoherenceEachLayer[nLayer];
   int iterMaxPixIdxEachLayer[nLayer];

   for(int iter=0; iter<numIter; iter++){

      if(8-5+iter >= 5){ // has >=5 chans in reco

         for(int layer=0; layer<nLayer; layer++){

            iterMaxPixIdxEachLayer[layer] = dummyData->iterMaxPixIdxEachLayer.at(iter*nLayer+layer);
            iterMaxPixCoherenceEachLayer[layer] = dummyData->iterMaxPixCoherenceEachLayer.at(iter*nLayer+layer);

         }

         TMath::Sort(nLayer, iterMaxPixCoherenceEachLayer, iterIndex);
         float iterZen = 90.f - onion.getPointing(iterMaxPixIdxEachLayer[iterIndex[0]]).theta * TMath::RadToDeg();
         iterZenVec.push_back(iterZen);

      }//end of if
   }//end of iter

   //float zenRange = 3.;
   zenMaj = getZenMaj(iterZenVec, zenRange);

   bool passSurfaceCut_2 = false;
   if(zenMaj <= 90 ){
      //iterMajorityZenHist->Fill(zenMaj,dummyData->weight);

      if(zenMaj < /*SURFACE_CUT_2*/surfaceCut_2 ){
         passSurfaceCut_2 = true;
      }

   } else passSurfaceCut_2 = true; //if no majority zenith can be found through iter reco, use solely the constantN zenith to is whether passed surface cut or not

   return !passSurfaceCut_2;
}

float getZenMaj(const vector<float>& iterZenVec, float zenRange){


   float zenMaj = 100.f;

   vector<int> cntVec;
   int maxCnt=0;
   int maxCntIdx = -1;

   for(int i=0; i<(int)iterZenVec.size(); i++){

      int cnt=0;

      for(int j=0; j<(int)iterZenVec.size(); j++){

         if(fabs(iterZenVec[i]-iterZenVec[j]) < zenRange) cnt++;

      }//end of j
      cntVec.push_back(cnt);
      if(cnt>maxCnt){

         maxCnt = cnt;
         maxCntIdx = i;

      } else if (cnt == maxCnt){

         if(iterZenVec[i] > iterZenVec[maxCntIdx]){ //pick the larger value if two angles have the same count
          maxCntIdx = i;
         }

      }

   }//end of i

   zenMaj = (maxCnt>1?iterZenVec[maxCntIdx]:100.f);
   return zenMaj;
}

bool isNearNoisyRun(const vector<int>& noisyRuns, int runNum, int plusMinusRunNum){


   bool isNoisy = false;

   for(int run=0; run<noisyRuns.size(); run++){
      if(fabs(noisyRuns[run] - runNum) <= plusMinusRunNum){
         isNoisy=true;
         break;
      }
   }

   return isNoisy;

}

bool isDeepPulser(string STATION, recoData *dummyData, int runNum){

   bool passDeepPulserCut = false;

   if( STATION == "ARA02" ){
      if( !(dummyData->unixTime < 1420.5122e6 && dummyData->unixTime > 1420.50905e6) && !(runNum >= 4795 && runNum <= 4800) && !(runNum == 4787 || runNum==4785 ) ){
         passDeepPulserCut = true;
      }
   }
   else if ( STATION == "ARA03" ){
      //to be implemented
   }

   return !passDeepPulserCut;
}

bool isCalpulserTime(string STATION, recoData *dummyData){

   bool passCalpulserTimeCut = false;
   if( STATION == "ARA02" ){
      if( !(dummyData->unixTime < 1393923046 && dummyData->unixTime > 1393917793) && !(dummyData->unixTime < 1395649842 && dummyData->unixTime > 1395648365) ){
         passCalpulserTimeCut = true;
      }
   } else if (STATION == "ARA03" ){
      if( !(dummyData->unixTime < 1393923742 && dummyData->unixTime > 1393922266) && !(dummyData->unixTime < 1395650418 && dummyData->unixTime > 1395648942) ){
         passCalpulserTimeCut = true;
      }
   }

   return !passCalpulserTimeCut;
}

bool isCalpulser(float &inBoxTheta, float &inBoxPhi, string STATION, recoData *dummyData, Healpix_Onion onion, recoSettings *settings, int type){

   ARA02_cutValues *cutValues;

   if(STATION == "ARA02") cutValues = new ARA02_cutValues();
   //ARA03: to be implemented

   bool inBox = false;
   bool passCalpulserCut = false;

   bool iterInBox = false;
   int inBoxCount = 0;
   inBoxTheta = 0.f;
   inBoxPhi   = 0.f;

   int nLayer = settings->nLayer;

   int nAnt = (string(settings->recoPolType)=="both"?16:8);
   int numIter = nAnt - settings->nchnlCut + 1;

   for(int iter=0; iter<numIter; iter++){

      //int maxPixIdx = dummyData->iterMaxPixIdx.at(iter);
      //float maxPixCoherence = dummyData->iterMaxPixCoherence.at(iter);
      int maxPixIdx = dummyData->iterMaxPixIdxEachLayer.at(iter*nLayer+0);
      float maxPixCoherence = dummyData->iterMaxPixCoherenceEachLayer.at(iter*nLayer+0);
      //cout<<"maxPixIdx: "<<maxPixIdx<<" layer: "<<maxPixIdx/nDir<<" maxPixCoherence: "<<maxPixCoherence<<endl;
      float theta = 90.f-TMath::RadToDeg()*onion.getPointing(maxPixIdx).theta;
      float phi   = TMath::RadToDeg()*onion.getPointing(maxPixIdx).phi;


      iterInBox = false;
      /*** Box 1 ***/
      ///if( theta > zenMin[0] && theta < zenMax[0] && phi > aziMin[0] && phi < aziMax[0] ) { inBox = true; iterInBox = true;}

      /*** Box 2 ***/
      //if( type != 3){
      //if( (theta > zenMin[1] && theta < zenMax[1] && phi > aziMin[1] && phi < aziMax[1]) ){ inBox = true; iterInBox = true;}
      //}

      if( STATION == "ARA02"){

         for(int box=0; box<cutValues->nBoxes; box++){

            // 0: D5BV, 1: D6BV, 2: D5BV Mirror, only for type 5
            if(box<2){

               if( theta > cutValues->zenMin[box].val && theta < cutValues->zenMax[box].val && phi > cutValues->aziMin[box].val && phi < cutValues->aziMax[box].val ) { inBox = true; iterInBox = true;}

            } else {

               if( type == 5 ){
                  if( theta > cutValues->zenMin[box].val && theta < cutValues->zenMax[box].val && phi > cutValues->aziMin[box].val && phi < cutValues->aziMax[box].val ) { inBox = true; iterInBox = true;}
               }
            }
         }
      } else {
         //ARA03: to be implemented
      }

      /*** Box 3 & 4 ***/
      //if ( type == 3 ){
      //   if( (theta > zenMin[2] && theta < zenMax[2] && phi > aziMin[2] && phi < aziMax[2])
      //     ||(theta > zenMin[3] && theta < zenMax[3] && phi > aziMin[3] && phi < aziMax[3])){ inBox = true; iterInBox = true;}
      //}

      if(iterInBox){
         inBoxCount++;
         inBoxTheta += theta;
         inBoxPhi   += phi;
      }

   }//end of iter

   //if (!inBox) passCalpulserCut = true;
   //else passSurfaceCut = false;

   if(inBoxCount > 0 ){

      inBoxTheta /= (float)inBoxCount;
      inBoxPhi   /= (float)inBoxCount;
   }

   delete cutValues;

   return inBox;
}

bool isRecoverableByImp(bool isVpolCW, bool isHpolCW, bool isXpolCW, recoData *dummyData, double impCut, double highPassFreq){

      double impulsivity[16];
      std::fill(&impulsivity[0], &impulsivity[16], 0.);
      double avgImpulsivity;

      bool passHighPassFilter = false;
      bool passImpulsivityCut = false;

      int nonZeroCount;

      //cout<<"isVpolCW: "<<isVpolCW<<" isHpolCW: "<<isHpolCW<<" isXpolCW: "<<isXpolCW<<endl;

      if((isVpolCW && isHpolCW) || isXpolCW){

      nonZeroCount = 0;
      double sum = 0.;
      for(int ch=0; ch<16; ch++){
         if(fabs( dummyData->impulsivity[ch] - 0 ) > 1e-9 ){
            nonZeroCount++;
            impulsivity[ch] = dummyData->impulsivity[ch];
            sum += impulsivity[ch];
         }
      }

      //int index[16];
      //TMath::Sort(16, impulsivity, index);
      avgImpulsivity = sum / (double)nonZeroCount;

      //impulsivityHist_max->Fill(impulsivity[index[0]], dummyData->weight);
      //impulsivityHist_3rd->Fill(impulsivity[index[2]], dummyData->weight);
      //impulsivityHist_avg->Fill(avgImpulsivity, dummyData->weight);
      //outputFile<<avgImpulsivity<<",";
      //thermalCWEventCount_both += dummyData->weight;

      if(dummyData->maxCountFreq_V > highPassFreq || dummyData->maxCountFreq_H > highPassFreq) passHighPassFilter = true;

      }

      else if( isVpolCW && !isHpolCW){

      nonZeroCount = 0;
      double sum = 0.;
      for(int ch=0; ch<8; ch++){
         if(fabs( dummyData->impulsivity[ch] - 0 ) > 1e-9 ){
            nonZeroCount++;
            impulsivity[ch] = dummyData->impulsivity[ch];
            sum += impulsivity[ch];
         }
      }

      //int index[16];
      //TMath::Sort(16, impulsivity, index);
      avgImpulsivity = sum / (double)nonZeroCount;

      //impulsivityHist_max->Fill(impulsivity[index[0]], dummyData->weight);
      //impulsivityHist_3rd->Fill(impulsivity[index[2]], dummyData->weight);
      //impulsivityHist_avg->Fill(avgImpulsivity, dummyData->weight);
      //outputFile<<avgImpulsivity<<",";
      //thermalCWEventCount_V += dummyData->weight;

      if(dummyData->maxCountFreq_V > highPassFreq ) passHighPassFilter = true;

      }

      else {

      nonZeroCount = 0;
      double sum = 0.;
      for(int ch=8; ch<16; ch++){
         if(fabs( dummyData->impulsivity[ch] - 0 ) > 1e-9 ){
            nonZeroCount++;
            impulsivity[ch] = dummyData->impulsivity[ch];
            sum += impulsivity[ch];
         }
      }

      //int index[16];
      //TMath::Sort(16, impulsivity, index);
      avgImpulsivity = sum / (double)nonZeroCount;

      //impulsivityHist_max->Fill(impulsivity[index[0]], dummyData->weight);
      //impulsivityHist_3rd->Fill(impulsivity[index[2]], dummyData->weight);
      //impulsivityHist_avg->Fill(avgImpulsivity, dummyData->weight);
      //outputFile<<avgImpulsivity<<",";
      //thermalCWEventCount_H += dummyData->weight;

      if(dummyData->maxCountFreq_H > highPassFreq ) passHighPassFilter = true;

      }
      //cout<<"maxCountFreq_V: "<<dummyData->maxCountFreq_V<<" maxCountFreq_H: "<<dummyData->maxCountFreq_H<<" avgImp: "<<avgImpulsivity<<" impCut: "<<impCut<<endl;
      if(avgImpulsivity > impCut){
         passImpulsivityCut = true;
         //nRecoveredByImp += dummyData->weight;
      }
      passHighPassFilter = true;
      //cout<<"passImpulsivityCut: "<<passImpulsivityCut<<" passHighPassFilter: "<<passHighPassFilter<<" return: "<<(passImpulsivityCut && passHighPassFilter)<<endl;
      return passImpulsivityCut && passHighPassFilter;
}


bool isBelowThermalImpulsivityCut(double& avgImpulsivity, recoData *dummyData, double postThermalAvgImpulsivityCut){

      double impulsivity[16];
      std::fill(&impulsivity[0], &impulsivity[16], 0.);
      int nonZeroCount = 0;
      double sum = 0.;

      avgImpulsivity = 0.;

      bool passThermalImpulsivityCut =  false;

      for(int ch=0; ch<8; ch++){
         if(fabs( dummyData->impulsivity[ch] - 0 ) > 1e-9 ){
            nonZeroCount++;
            impulsivity[ch] = dummyData->impulsivity[ch];
            sum += impulsivity[ch];
         }
      }

      int index[16];
      TMath::Sort(16, impulsivity, index);
      avgImpulsivity = sum / (double)nonZeroCount;
      if(avgImpulsivity > postThermalAvgImpulsivityCut){

         //outputFile<<runNum<<","<<dummyData->eventNumber<<","<<dummyData->unixTime<<endl;
         passThermalImpulsivityCut = true;

      } else {
         passThermalImpulsivityCut = false;
      }

      return !passThermalImpulsivityCut;
}
