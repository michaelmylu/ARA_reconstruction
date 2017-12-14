#include "trackEngine.h"
#include "TObject.h"

//ClassImp(trackEngine)
//ClassImp(Vector)

using namespace std;

trackEngine::trackEngine(){}

trackEngine::~trackEngine(){

  clearAll();

}

int trackEngine::buildBaselineTracks(const vector< vector<double> >& antLocation){

/*
   int numStr = (int)detector->stations[0].size();
   int numAnt = (int)detector->stations[0].strings[0].size();
   cout<<"Number of strings: "<<numStr<<" Number of antennas per string: "<<numAnt<<endl;
*/

   int nAnt = (int)antLocation.size();
   if(nAnt <= 0){ cerr<<"antLocation wrong size\n"; return -1; }
   Vector uVec;
   vector<Vector> tempVec;
   vector<double> tempTime;
   double dx, dy, dz, norm, dt;

   for(int ant1=0; ant1<nAnt; ant1++){

     tempVec.clear();
     tempTime.clear();
     for(int ant2=0; ant2<nAnt; ant2++){

       dx = antLocation[ant2][0] - antLocation[ant1][0];
       dy = antLocation[ant2][1] - antLocation[ant1][1];
       dz = antLocation[ant2][2] - antLocation[ant1][2];
       uVec.SetXYZ(dx, dy, dz);
       cout<<"ant1: "<<ant1<<" ant2: "<<ant2<<" norm "<<uVec.Mag()<<endl;
       uVec.Print();
       dt = uVec.Mag() * nIce / speedOfLight;
       tempTime.push_back(dt);
       if(uVec.Mag()==0) tempVec.push_back(zeroVector);
       else              tempVec.push_back(uVec.Unit());
       cout<<"Unit norm: "<<tempVec[ant2].Mag()<<" tempTime: "<<tempTime[ant2]<<endl;

      }
   baselineTrackTimes.push_back(tempTime);
   baselineTracks.push_back(tempVec);
   }

   if(checkBaselineTracks() > 1e-9 ){ cerr<<"Sum of all baseline tracks !=0!\n"; return -1;}

   return 0;
}

int trackEngine::computeFinalTracks(vector<TGraph* > unpaddedEvent){

   double peakTArray[16];
   float snrArray[16];
   int index[16];
   getChannelSNR(unpaddedEvent, snrArray);
   TMath::Sort(16,snrArray,index);
   getChannelPeakTime(unpaddedEvent, peakTArray);

   int nAnt = (int)unpaddedEvent.size();
   //int nTracks = TMath::Binomial(nAnt, 2);
   //cout<<"nTracks: "<<nTracks<<endl;
   trackRank = (int*)calloc(nAnt*nAnt, sizeof(int));
   trackSNRArray = (float*)calloc(nAnt*nAnt, sizeof(float));

   for(int ant1=0; ant1<nAnt; ant1++){
      for(int ant2=0; ant2<nAnt; ant2++){
        trackSNRArray[ant1*nAnt+ant2] = (snrArray[ant1]+snrArray[ant2]) / 2.; //Take the average SNR as the pair SNR
      }
   }

   TMath::Sort(nAnt*nAnt, trackSNRArray, trackRank);

   //double cosine;
   goodTrackCount = 0;
   badTrackCount  = 0;
   cosine = (double*)malloc(sizeof(double)*nAnt*nAnt);

   for(int anti=0; anti<nAnt; anti++){
     for(int antf=0; antf<nAnt; antf++){

       if(peakTArray[anti]>-1e9 && peakTArray[antf]>-1e-9){
         if(fabs(peakTArray[anti]-peakTArray[antf]) < baselineTrackTimes[anti][antf] + tolerance){

           goodTrackCount++;

           //if(peakTArray[anti] > peakTArray[antf]){

          //   cosine[anti*nAnt+antf] = -1.* (peakTArray[anti] - peakTArray[antf]) / baselineTrackTimes[anti][antf];

           //} else {
           if(anti != antf)
            cosine[anti*nAnt+antf] = (peakTArray[antf] - peakTArray[anti]) / baselineTrackTimes[anti][antf];
           else
            cosine[anti*nAnt+antf] = 0.;

           if(cosine[anti*nAnt+antf] > 1) cosine[anti*nAnt+antf] = 1.;

           //}
           demoFinalTrack += (cosine[anti*nAnt+antf] * baselineTracks[anti][antf]);

         } else {

           badTrackCount++;
           cosine[anti*nAnt+antf] = -1e9;

         }//end of else
       }//end of if t > -1e9
       else {
         badTrackCount++;
         cosine[anti*nAnt+antf] = -1e9;
       }
     }//end of antf
   }//end of anti

   demoFinalTrack = demoFinalTrack / 2.; //acoount for double counting
   Vector tempVector;
   tempVector.SetXYZ(0.,0.,0.);
   for(int rank=0; rank<nAnt*nAnt; rank++){

     int anti = trackRank[rank]/nAnt;
     int antf = trackRank[rank]%nAnt;

     if(cosine[anti*nAnt+antf] > -1e9){
     if( (tempVector+(cosine[anti*nAnt+antf]*baselineTracks[anti][antf])).Mag() > tempVector.Mag() ){

       tempVector += (cosine[anti*nAnt+antf]*baselineTracks[anti][antf]);

     }
     }
   }//end of rank

   if(tempVector.Mag() < 1e-9){ cerr<<"hierFinalTrack lenght is zero!\n"; return -1;}
   else hierFinalTrack = (tempVector / 2.); //account for double counting

   return 0;
}

int trackEngine::getChannelPeakTime(vector<TGraph *> unpaddedEvent, double *peakTArray){

  double peakV, peakT, v, t;
  peakV = 0.;
  peakT = -1e10;

   for(int ch=0; ch<unpaddedEvent.size(); ch++){
      for(int i=0; i<unpaddedEvent[ch]->GetN(); i++){

         unpaddedEvent[ch]->GetPoint(i, t, v);
         if( fabs(v) > peakV ){ peakV = fabs(v); peakT = t; }

      }
      peakTArray[ch] = peakT;
   }

   return 0;
}

double trackEngine::checkBaselineTracks(){

  Vector tempVector;
  tempVector.SetXYZ(0.,0.,0.);

  for(int ant1=0; ant1<baselineTracks.size(); ant1++){
    for(int ant2=0; ant2<baselineTracks.size(); ant2++){

      tempVector += baselineTracks[ant1][ant2];

    }
  }
  return tempVector.Mag();
}

/*
int computeExtrapFinalTracksWithDemo(){

  vector<Vector> tempVector;
  Vector temp;
  double rotAngle;
  int nAnt = (int)baselineTracks.size();

  for(int anti=0; anti<nAnt; ant1++){

    tempVector.clear();
    for(int antf=0; antf<nAnt; ant2++){
      rotAngle = TMath::Pi()/2. - demoFinalTrack.Angle(baselineTracks[anti][antf]);
      temp = demoFinalTrack.Rotate(rotAngle, baselineTracks[anti][antf].Cross(demoFinalTrack));
      temp = temp / temp.Mag();
      temp = temp * sqrt(1-cosine[anti*nAnt+antf]*cosine[anti*nAnt+antf]);
      tempVector.push_back(temp);
    }
    eventOrthoTracks.push_back(tempVector);
  }

  demoExtrapFinalTrack = (demoFinalTrack * 2.)

  for(int anti=0; anti<nAnt; anti++){
    for(int antf=0; antf<nAnt; antf++){

      if(cosine[anti*nAnt+antf]> -1e9){
        demoExtrapFinalTrack += eventOrthoTracks[anti][antf];
      }
    }
  }

  demoExtrapFinalTrack = demoExtrapFinalTrack / 2.;

  Vector tempVector;
  tempVector.SetXYZ(0.,0.,0.);
  for(int rank=0; rank<nAnt*nAnt; rank++){

    anti = trackRank[rank]/nAnt;
    antf = trackRank[rank]%nAnt

    if(cosine[anti*nAnt+antf] > -1e9){
    if( (tempVector
        + baselineTracks[anti][antf]*cosine[anti*nAnt+antf]
        + eventOrthoTracks[anti][antf]
        ).Mag() > tempVector.Mag() ){

      tempVector += (baselineTracks[anti][antf]*cosine[anti*nAnt+antf] + eventOrthoTracks[anti][antf]);

    }
    }
  }//end of rank

  if(tempVector.Mag() < 1e-9){ cerr<<"hierExtrapFinalTrack lenght is zero!\n"; return -1;}
  else hierExtrapFinalTrack = (tempVector / 2.); //account for double counting

  return 0;
}

int computeExtrapFinalTracksWithHier(){

  vector<Vector> tempVector;
  Vector temp;
  double rotAngle;
  int nAnt = (int)baselineTracks.size();

  for(int anti=0; anti<nAnt; ant1++){

    tempVector.clear();
    for(int antf=0; antf<nAnt; ant2++){
      rotAngle = TMath::Pi()/2. - hierFinalTrack.Angle(baselineTracks[anti][antf]);
      temp = hierFinalTrack.Rotate(rotAngle, baselineTracks[anti][antf].Cross(hierFinalTrack));
      temp = temp / temp.Mag();
      temp = temp * sqrt(1-cosine[anti*nAnt+antf]*cosine[anti*nAnt+antf]);
      tempVector.push_back(temp);
    }
    eventOrthoTracks.push_back(tempVector);
  }

  demoExtrapFinalTrack = (demoFinalTrack * 2.)

  for(int anti=0; anti<nAnt; anti++){
    for(int antf=0; antf<nAnt; antf++){

      if(cosine[anti*nAnt+antf]> -1e9){
        demoExtrapFinalTrack += eventOrthoTracks[anti][antf];
      }
    }
  }

  demoExtrapFinalTrack = demoExtrapFinalTrack / 2.;

  Vector tempVector;
  tempVector.SetXYZ(0.,0.,0.);
  for(int rank=0; rank<nAnt*nAnt; rank++){

    anti = trackRank[rank]/nAnt;
    antf = trackRank[rank]%nAnt

    if(cosine[anti*nAnt+antf] > -1e9){
    if( (tempVector
        + baselineTracks[anti][antf]*cosine[anti*nAnt+antf]
        + eventOrthoTracks[anti][antf]
        ).Mag() > tempVector.Mag() ){

      tempVector += (baselineTracks[anti][antf]*cosine[anti*nAnt+antf] + eventOrthoTracks[anti][antf]);

    }
    }
  }//end of rank

  if(tempVector.Mag() < 1e-9){ cerr<<"hierExtrapFinalTrack lenght is zero!\n"; return -1;}
  else hierExtrapFinalTrack = (tempVector / 2.); //account for double counting

  return 0;
}
*/
//int computeExtrapFinalTracks(Vector finalTrack){
int trackEngine::buildEventOrthoTracks(Vector finalTrack){

  eventOrthoTracks.clear();
  if(finalTrack.Mag() == 0){ cerr<<"No finalTrack!\n"; return -1;}
  vector<Vector> tempVector;
  Vector temp;
  double rotAngle;
  int nAnt = (int)baselineTracks.size();
  if(nAnt == 0){ cerr<<"No baselineTracks!\n"; return -1;}

  for(int anti=0; anti<nAnt; anti++){

    tempVector.clear();
    for(int antf=0; antf<nAnt; antf++){
      if(cosine[anti*nAnt+antf] > -1e9 && anti!=antf){
      rotAngle = TMath::Pi()/2. - finalTrack.Angle(baselineTracks[anti][antf]);
      temp = finalTrack.Rotate(rotAngle, baselineTracks[anti][antf].Cross(finalTrack));
      temp = temp / temp.Mag();
      temp = sqrt(1-cosine[anti*nAnt+antf]*cosine[anti*nAnt+antf]) * temp;
      tempVector.push_back(temp);
    } else { tempVector.push_back(zeroVector); }
    }
    eventOrthoTracks.push_back(tempVector);
  }

  return 0;
}

Vector trackEngine::computeDemoExtrapFinalTrack(){

  if(demoFinalTrack.Mag()==0 ){ cerr<<"No demoFinalTrack\n"; return zeroVector;}
  //demoExtrapFinalTrack = (demoFinalTrack * 2.)
  Vector deft = (2. * demoFinalTrack );

  if(eventOrthoTracks.size()==0){ cerr<<"No eventOrthoTracks\n"; return zeroVector;}

  int nAnt = (int)baselineTracks.size();

  for(int anti=0; anti<nAnt; anti++){
    for(int antf=0; antf<nAnt; antf++){

      if(cosine[anti*nAnt+antf]> -1e9){
        /*demoExtrapFinalTrack*/deft += eventOrthoTracks[anti][antf];
      }
    }
  }

  //demoExtrapFinalTrack = demoExtrapFinalTrack / 2.;
  deft = deft / 2.;

  //return demoExtrapFinalTrack;
  return deft;
}

Vector trackEngine::computeHierExtrapFinalTrack(){

  if(eventOrthoTracks.size()==0){ cerr<<"No eventOrthoTracks\n"; return zeroVector;}
  int nAnt = (int)baselineTracks.size();
  Vector tempVector;
  tempVector.SetXYZ(0.,0.,0.);
  for(int rank=0; rank<nAnt*nAnt; rank++){

    int anti = trackRank[rank]/nAnt;
    int antf = trackRank[rank]%nAnt;

    if(cosine[anti*nAnt+antf] > -1e9){
    if( (tempVector
        + (cosine[anti*nAnt+antf]*baselineTracks[anti][antf])
        + eventOrthoTracks[anti][antf]
        ).Mag() > tempVector.Mag() ){

      tempVector += (cosine[anti*nAnt+antf]*baselineTracks[anti][antf] + eventOrthoTracks[anti][antf]);

    }
    }
  }//end of rank

  if(tempVector.Mag() < 1e-9){ cerr<<"hierExtrapFinalTrack lenght is zero!\n"; return zeroVector;}
  else /*hierExtrapFinalTrack*/tempVector = (tempVector / 2.); //account for double counting

  //return hierExtrapFinalTrack.Mag();
  return tempVector;
}


int trackEngine::computeIterExtrapFinalTracks(Vector tempDemoExtrap, Vector tempHierExtrap){

if(tempDemoExtrap.Mag()==0 || tempHierExtrap.Mag()==0 ){ cerr<"No input demo/hier final track\n"; return -1;}
  //Vector tempDemoExtrap = demoExtrapFinalTrack;
  //Vector tempHierExtrap = hierExtrapFinalTrack;

  int demoCount = 0;
  int hierCount = 0;
  int count = 0;
  double demoAngle, hierAngle;

  //Iterate demo extrap track
  do {

    if( buildEventOrthoTracks(tempDemoExtrap)<0 ){ cerr<<"Re-building ortho tracks error\n"; return -1; }
    iterDemoExtrapFinalTrack = computeDemoExtrapFinalTrack();
    if( iterDemoExtrapFinalTrack.Mag() != 0 ){
      demoAngle = tempDemoExtrap.Angle(iterDemoExtrapFinalTrack) * TMath::RadToDeg();
      //hierAngle = tempHierExtrap.Angle(hierExtrapFinalTrack) * TMath::RadToDeg();
      tempDemoExtrap = iterDemoExtrapFinalTrack;
      //tempHierExtrap = hierExtrapFinalTrack;
    } else {
      cerr<<"compute demo extrapolated final track error\n"; return -1;
    }
    demoCount++;
  } while(demoAngle < angleThreshold || demoCount < maxIteration); //Stopping condition: when the space angle converges or when done max iterations

  //Iterate hier extrap track
  do {

    if( buildEventOrthoTracks(tempHierExtrap)<0 ){ cerr<<"Re-building ortho tracks error\n"; return -1; };
    iterHierExtrapFinalTrack = computeHierExtrapFinalTrack();
    if( iterHierExtrapFinalTrack.Mag() != 0 ){
      //demoAngle = tempDemoExtrap.Angle(iterDemoExtrapFinalTrack) * TMath::RadToDeg();
      hierAngle = tempHierExtrap.Angle(iterHierExtrapFinalTrack) * TMath::RadToDeg();
      //tempDemoExtrap = iterDemoExtrapFinalTrack;
      tempHierExtrap = iterHierExtrapFinalTrack;
    } else {
      cerr<<"compute hier extrapolated final track error\n"; return -1;
    }
    hierCount++;
  } while(hierAngle < angleThreshold || hierCount < maxIteration); //Stopping condition: when the space angle converges or when done max iterations

  cout<<"Demo count: "<<demoCount<<" Demo angle: "<<demoAngle<<endl;
  cout<<"Hier count: "<<hierCount<<" Hier angle: "<<hierAngle<<endl;

  return 0;
}

void trackEngine::initialize(){

  this->clearAll();
  this->setTolerance(5.);
  this->setAngleThreshold(1.);
  this->setMaxIteration(100);

}

void trackEngine::setTolerance(double tol){

  tolerance = tol;

}

void trackEngine::setAngleThreshold(double ang_thres){

    angleThreshold = ang_thres;

}

void trackEngine::setMaxIteration(int max_iter){

  maxIteration = max_iter;

}

void trackEngine::clearForNextEvent(){

  //baselineTracks.clear();
  //baselineTrackTimes.clear();
  eventOrthoTracks.clear();

  goodTrackCount = badTrackCount = 0;
  free(trackRank);
  free(trackSNRArray);
  free(cosine);

  demoFinalTrack = hierFinalTrack = demoExtrapFinalTrack = hierExtrapFinalTrack
  = iterDemoExtrapFinalTrack = iterHierExtrapFinalTrack = zeroVector;

  //angleThreshold = 0.;
  //maxIteration = 0;

}

void trackEngine::clearAll(){

  baselineTracks.clear();
  baselineTrackTimes.clear();
  eventOrthoTracks.clear();

  goodTrackCount = badTrackCount = 0;
  free(trackRank);
  free(trackSNRArray);
  free(cosine);

  demoFinalTrack = hierFinalTrack = demoExtrapFinalTrack = hierExtrapFinalTrack
  = iterDemoExtrapFinalTrack = iterHierExtrapFinalTrack = zeroVector;

  angleThreshold = 0.;
  maxIteration = 0;
  tolerance = 0.;

}

int trackEngine::computeAllTracks(/*const vector< vector<double> >& antLocation,*/ vector<TGraph *> unpaddedEvent){

  //initialize();
  if(baselineTracks.size()==0){ cerr<<"No baseline tracks\n"; return -1;}
  //if( buildBaselineTracks(antLocation) < 0 ){ cerr<<"Build baseline tracks error\n"; return -1;}
  if( computeFinalTracks(unpaddedEvent) < 0 ){ cerr<<"Compute final tracks error\n"; return -1;}
  if( buildEventOrthoTracks(demoFinalTrack) < 0){ cerr<<"buildEventOrthoTracks with demo error\n"; return -1;}
  demoExtrapFinalTrack = computeDemoExtrapFinalTrack();
  if( buildEventOrthoTracks(hierFinalTrack) < 0){ cerr<<"buildEventOrthoTracks with hier error\n"; return -1;}
  hierExtrapFinalTrack = computeHierExtrapFinalTrack();
  if(demoExtrapFinalTrack.Mag() == 0 ){ cerr<<"No demoExtrapFinalTrack\n"; return -1;}
  if(hierExtrapFinalTrack.Mag() == 0 ){ cerr<<"No hierExtrapFinalTrack\n"; return -1;}
  if( computeIterExtrapFinalTracks(demoExtrapFinalTrack, hierExtrapFinalTrack) < 0){ cerr<<"Compute iter extrap final tracks error\n"; return -1;}

  //clearForNextEvent();

  return 0;
}

void trackEngine::print(){

  cout<<"demoFinalTrack.Mag(): "<<demoFinalTrack.Mag()<<endl;
  demoFinalTrack.Print();
  cout<<"hierFinalTrack.Mag(): "<<hierFinalTrack.Mag()<<endl;
  hierFinalTrack.Print();
  cout<<"demoExtrapFinalTrack.Mag(): "<<demoExtrapFinalTrack.Mag()<<endl;
  demoExtrapFinalTrack.Print();
  cout<<"hierExtrapFinalTrack.Mag(): "<<hierExtrapFinalTrack.Mag()<<endl;
  hierExtrapFinalTrack.Print();
  cout<<"iterDemoExtrapFinalTrack.Mag(): "<<iterDemoExtrapFinalTrack.Mag()<<endl;
  iterDemoExtrapFinalTrack.Print();
  cout<<"iterHierExtrapFinalTrack.Mag(): "<<iterHierExtrapFinalTrack.Mag()<<endl;
  iterHierExtrapFinalTrack.Print();


}