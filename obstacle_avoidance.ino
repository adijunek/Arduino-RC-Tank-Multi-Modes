#define MIN_DISTANCE 25 // distance to obstacle that triger avoidance behaviour 

int maxStep = 20; // initial angle for look left and look right
int addStep = 10; // incrementing angle if the last 'look arround' failed 

int obstacle = 0;
int countLeft = 0;
int countRight = 0;
int goLookLeft = 1;
int goLookRight = 0;

int rDistance;
int lDistance;

void avoidanceMode(){
  if(obstacle == 1){
    lookArround(maxStep);
  }else{
     moveForward();
  }  
}

void lookArround(int maxStep){

      //rotate left first 
      if(goLookLeft == 1){
          if(countLeft <= maxStep){ // look left
            rMotor.setSpeed(255);
            lMotor.setSpeed(255);
            rMotor.run(FORWARD);
            lMotor.run(BACKWARD);
            countLeft++;
          }else{
            mStop();
            countLeft=0;      
            goLookLeft=0;
            goLookRight=1;
            lDistance=readPing();
          }        
      }

      //than rotate right
      if(goLookRight == 1){
          if(countRight <= (2*maxStep)){ //look right
            rMotor.setSpeed(255);
            lMotor.setSpeed(255);
      
            rMotor.run(BACKWARD);
            lMotor.run(FORWARD);
            countRight++;
            
          }else{
            mStop();
            countRight = 0;            
            goLookRight=0;
            rDistance=readPing();
          }
        
      }

      /* decision based on left distance and right distance
       * 
       */
      if(goLookLeft == 0 && goLookRight == 0){
        digitalWrite(relay, LOW);
          if(rDistance >= lDistance && rDistance  > MIN_DISTANCE){
              obstacle = 0;
              goLookLeft = 1;    
          }else if(lDistance > rDistance && lDistance > MIN_DISTANCE){
              goLookLeft = 0;

              if(countLeft <= (2*maxStep)){
                  rMotor.setSpeed(255);
                  lMotor.setSpeed(255);
                  rMotor.run(FORWARD);
                  lMotor.run(BACKWARD);
                  countLeft++;
              }else{
                  mStop();
                  obstacle = 0;
                  goLookLeft = 1;
              }

              
          }else{
              
              maxStep+=addStep;
          }
      }                  

}

void moveForward(){
    rMotor.setSpeed(255);
    lMotor.setSpeed(255);

    rMotor.run(FORWARD);
    lMotor.run(FORWARD);

    int distance=readPing();

    if(distance <= MIN_DISTANCE){
        mStop();
        obstacle = 1;
    }
  
}

void resetAvoidance(){
    obstacle = 0;
    countLeft = 0;
    countRight = 0;
    goLookLeft = 1;
    goLookRight = 0;
}
