#include "Craneplus.h"
int main()
{
  Craneplus crane;
  double JointPos[ARM_FREEDOM-1];
  char *a;
  char s[] = "/dev/ttyUSB0";
  a = s;
  printf("openserialport\n");
  crane.OpenCOMDevice(a);
  printf("initArm\n");
  crane.initArm();

int c;

  std::cout << "コマンドを選択してください" << std::endl;
  std::cout << "1 : サーボON" << std::endl;
  std::cout << "2 : サーボOFF" << std::endl;
  std::cout << "3 : アーム先端の移動" << std::endl;
  std::cout << "4 : アーム関節の回転" << std::endl;
  std::cout << "5 : アーム先端座標の計算" << std::endl;
  std::cout << "6 : グリッパ開閉" << std::endl;
  std::cout << "7 : グリッパ閉" << std::endl;
  std::cout << "8 : グリッパ開" << std::endl;
  std::cout << "9 : 終了" << std::endl;


  std::cout << ">>";
  std::cin >> c; 
  std::cout << std::endl; 

  if(c == 1)
    {
      crane.ServoOnOff(1);
    }
  else if(c == 2)
    {
      crane.ServoOnOff(0);
    }
  else if(c == 3)
    {
      double x;
      double y;
      double z;
      
      std::cout << "座標を入力してください" << std::endl;
      std::cout << "x座標 : "; 
      std::cin >> x;
      std::cout << "y座標 : ";
      std::cin >> y;
      std::cout << "z座標 : ";
      std::cin >> z;
      std::cout << std::endl; 
      
      crane.kinematics(x,y,z,JointPos);
      crane.setCRANEJointdata(JointPos);  
      crane.ArmAction();
    }
  
  else if(c == 4)
    {
      std::cout << "下からグリッパに向かって第1関節〜第4関節" << std::endl << "関節角度を入力してください　単位[°]" << std::endl;
      std::cout << "第1関節の角度 : ";
      std::cin >>JointPos[0];
      std::cout << "第2関節の角度 : ";
      std::cin >>JointPos[1];
      std::cout << "第3関節の角度 : ";
      std::cin >>JointPos[2];
      std::cout << "第4関節の角度 : ";
      std::cin >>JointPos[3];
      std::cout << std::endl; 
      
      crane.setCRANEJointdata(JointPos);   
      crane.ArmAction();
    }

  else if(c == 5)
    {
      crane.getCRANEJointdata(JointPos);
      std::cout << "現在値" << std::endl;
      std::cout << "JointPos[0] = " << JointPos[0] << std::endl;
      std::cout << "JointPos[1] = " << JointPos[1] << std::endl;
      std::cout << "JointPos[2] = " << JointPos[2] << std::endl;
      std::cout << "JointPos[3] = " << JointPos[3] << std::endl;
    }  
  
  else if(c == 6)
    {
      double angleRatio;
      std::cout << "開度を入力してください 1~100[%]" << std::endl;
      std::cout << ">>";
      std::cin >> angleRatio;
      std::cout << std::endl; 
      
      if(angleRatio >= 1 && angleRatio <=100){
        crane.CRANEmoveGripper(angleRatio);
      }
      else 
	std::cout << "無効な値です" << std::endl;
    }

  else if(c == 7)
    {
      crane.CRANEcloseGripper();
    }
  
  else if (c == 8)
    {
      crane.CRANEopenGripper();
    }
  
  else if(c == 9)
    {
      std::cout << "END" << std::endl;
      crane.CloseCOMDevice();
      return 0;
    }
  
  else 
    std::cout << "無効な値です" << std::endl<<std::endl;
  
  crane.CloseCOMDevice();

  return 0;
}
