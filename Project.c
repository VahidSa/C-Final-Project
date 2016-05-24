#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Date{
	int Day;
	int Month;
	int Year;
};
struct Product{
	char Name[10];
	char CompanyName[10];
	double Price;
	int Id;
	struct Date ExpirationDate;
};
struct Product *pro;
void recovery();
void Menu();
void Add();
void Search();
void Show();
void Sort();
void Update();
void Delete();
int main(){
	int n=0;
	FILE *FPN;
	FPN=fopen("FilePN.bin","wb");
	if(!FPN){printf("couldn't allocate memory\n");}
	fwrite(&n , sizeof(int) , 1 , FPN);
	fclose(FPN);
	Menu();
	return 0;
}
void Menu(){
	int x;
	printf(" 1.Add \n 2.Show \n 3.Search \n 4.Update \n 5.Sort \n 6.Delete \n 7.Recovery \n 8.Exit \n");
	scanf("%d",&x);
	switch(x){
		case 1:
			Add();
			break;
		case 2:
			Show();
			break;
		case 3:
			Search();
			break;
		case 4:
			Update();
			break;
		case 5:
			Sort();
			break;
		case 6:
			Delete();
			break;
		case 7:
		//	save
			break;
		case 8:
			recovery();
			break;
		case 9:
			exit(0);
			break;
		default:
			exit(0);
			break;
	}
}
void Delete(){
	int x,nt,i,ki,k,id;
	FILE *FPN;
	FPN=fopen("FilePN.bin","rb");
	fread(&nt , sizeof(int) , 1 , FPN);
	fclose(FPN);
	struct Product *pro;
	pro=malloc(sizeof(struct Product)*nt);
	FILE *FP;
	FP=fopen("File.bin","rb");
	fread(pro, sizeof(struct Product), nt, FP);
	fclose(FP);
	FILE *RV;
	printf("1.Delete \n 2.Shift+Delete");
	scanf("%d",&x);
	struct Product Temp;
	switch(x){
		case 1:
			printf("Enter Id of product: ");
			scanf("%d",&id);
			for(i=0;i<nt;i++)
				if(pro[i].Id==id){
					ki=i;
					k=1;
					break;
				}
			Temp=pro[ki];
			RV=fopen("Trash.bin","wb");
			fwrite(&Temp, sizeof(struct Product), 1 , RV);
			//fwrite(ki, sizeof(int), 1 , rv);
			fclose(RV);
			
			/*
			RV=fopen("Trash.bin","rb");
			fread(&Temp , sizeof(struct Product) , 1 , RV);
			fclose(RV);
		///			D		///
			printf("Product Name: %s\n",Temp.Name);
			printf("Product Company Name: %s\n",Temp.CompanyName);
			printf("Product Price: %lf\n",Temp.Price);
			printf("Product ExpirationDate: %d/%d/%d\n", Temp.ExpirationDate.Year, pro[ki].ExpirationDate.Month, pro[ki].ExpirationDate.Day);
			printf("Product Id: %d\n",Temp.Id);
		///			D		///
			
			*/
			
			if(k==1)
				for(;ki<nt;ki++)
					pro[ki]=pro[ki+1];
			else
				printf("Not Found!");
		break;
		case 2:
			printf("Enter Id of product: ");
			scanf("%d",&id);
			for(;i<nt;i++)
				if(pro[i].Id==id){
					ki=i;
					k=1;
					break;
				}
			if(k==1)
				for(;ki<nt;ki++)
					pro[ki]=pro[ki+1];
			else
				printf("Not Found!");
		break;
	}
	FP=fopen("File.bin","wb");
	fwrite(pro,sizeof(struct Product),nt,FP);
	fclose(FP);
	nt--;
	FPN=fopen("FilePN.bin","wb");
	fwrite(&nt , sizeof(int) , 1 , FPN);
	fclose(FPN);
	//free(pro);
	Menu();
}
void recovery(){
	int nt;
	int i;	//D
	struct Product Temp;
	//struct Product *pro;
	FILE *FPN;
	FPN=fopen("FilePN.bin","rb");
	fread(&nt , sizeof(int) , 1 , FPN);
	fclose(FPN);	
	nt++;
	FPN=fopen("FilePN.bin","wb");
	fwrite(&nt,sizeof(int),1,FPN);
	fclose(FPN);
//	pro=malloc(sizeof(struct Product)*nt);
	FILE *RV;
	RV=fopen("Trash.bin","rb");
	fread(&Temp , sizeof(struct Product) , 1 , RV);
	fclose(RV);
	FILE *FP;
	
	/*
	FP=fopen("File.bin","rb");
	fread(pro , sizeof(struct Product) , nt-1 , FP);
	fclose(FP);
	pro[nt]=Temp;
	FP=fopen("File.bin","wb");
	fwrite(pro,sizeof(struct Product),nt,FP);
	fclose(FP);
	*/
	
	
	///			D		///
	printf("Product Name: %s\n",Temp.Name);
	printf("Product Company Name: %s\n",Temp.CompanyName);
	printf("Product Price: %lf\n",Temp.Price);
	printf("Product ExpirationDate: %d/%d/%d\n", Temp.ExpirationDate.Year, Temp.ExpirationDate.Month, Temp.ExpirationDate.Day);
	printf("Product Id: %d\n",Temp.Id);
	///			D		///
			
	
	/*
	FP=fopen("File.bin","ab");
	fwrite(&Temp,sizeof(struct Product), 1 , FP);
	fclose(FP);
	*/
	
	///		D		///
	nt--;
	struct Product *pro;
	FP=fopen("File.bin","rb");
	pro=malloc(sizeof(struct Product)*nt);
	fread(pro,sizeof(struct Product), nt , FP);
	fclose(FP);
	printf("%d\n",nt);//D
	for(i=0;i<nt;i++){
		printf("Details of product %d \n",i+1);
		printf("Product Name: %s\n",pro[i].Name);
		printf("Product Company Name: %s\n",pro[i].CompanyName);
		printf("Product Price: %lf\n",pro[i].Price);
		printf("Product ExpirationDate: %d/%d/%d\n", pro[i].ExpirationDate.Year, pro[i].ExpirationDate.Month, pro[i].ExpirationDate.Day);
		printf("Product Id: %d\n",pro[i].Id);
	}
	
	///		D		///
	
	
	//free(pro);
	Menu();
}
void Update(){
	int id,nt,i,ki,k=0;
	FILE *FPN;
	FPN=fopen("FilePN.bin","rb");
	fread(&nt , sizeof(int) , 1 , FPN);
	fclose(FPN);
	struct Product *pro;
	pro=malloc(sizeof(struct Product)*nt);
	FILE *FP;
	FP=fopen("File.bin","rb");
	fread(pro, sizeof(struct Product), nt, FP);
	fclose(FP);
	printf("Enter id of Product For Edit: ");
	scanf("%d",&id);
	for(i=0;i<nt;i++)
		if(pro[i].Id==id){
			ki=i;
			k=1;
		}
	if(k==0)
		printf("This Product there isnt!");
	else{
			printf("Enter New Details of Product Name %d:\n",i+1);
			printf("Enter Product Name: ");
			scanf("%s",pro[ki].Name);
			printf("Enter Product Company Name: ");
			scanf("%s",pro[ki].CompanyName);
			printf("Enter Product Price: ");
			scanf("%lf",&pro[ki].Price);
			printf("Enter Product ExpirationDate: \n");
			printf("Enter Product ExpirationDate Day: ");
			scanf("%d",&pro[ki].ExpirationDate.Day);
			printf("Enter Product ExpirationDate Month: ");
			scanf("%d",&pro[ki].ExpirationDate.Month);
			printf("Enter Product ExpirationDate Year: ");
			scanf("%d\n",&pro[ki].ExpirationDate.Year);
	}
	FP=fopen("File.bin","wb");
	fwrite(pro,sizeof(struct Product),nt,FP);
	fclose(FP);
	//free(pro);
	Menu();
}
void Sort(){
	int x,i,j,nt;
	struct Product Temp;
	FILE *FPN;
	FPN=fopen("FilePN.bin","rb");
	fread(&nt , sizeof(int) , 1 , FPN);
	fclose(FPN);
	struct Product *pro;
	pro=malloc(sizeof(struct Product)*nt);
	FILE *FP;
	FP=fopen("File.bin","rb");
	fread(pro, sizeof(struct Product), nt, FP);
	fclose(FP);
	printf("1.Ascending \n 2.Descending");
	scanf("%d",&x);
	switch(x){
		case 1:
			for(j=0;j<nt-1;j++)
				for(i=0;i<nt;i++)
					if(pro[i].Price<pro[i+1].Price){
						Temp=pro[i];
						pro[i]=pro[i+1];
						pro[i+1]=Temp;
					}
		break;
		case 2:
			for(j=0;j<nt-1;j++)
				for(i=0;i<nt-1;i++)
					if(pro[i].Price>pro[i+1].Price){
						Temp=pro[i];
						pro[i]=pro[i+1];
						pro[i+1]=Temp;
					}
		break;
	}
	FP=fopen("File.bin","wb");
	fwrite(pro,sizeof(struct Product),nt,FP);
	fclose(FP);
	//free(pro);
	Menu();
}
void Search(){
	int i,nt,counter=0;
	//int k,j;
	char s[13];
	FILE *FPN;
	FPN=fopen("FilePN.bin","rb");
	fread(&nt , sizeof(int) , 1 , FPN);
	fclose(FPN);
	struct Product *pro;
	pro=malloc(sizeof(struct Product)*nt);
	FILE *FP;
	FP=fopen("File.bin","rb");
	fread(pro, sizeof(struct Product), nt, FP);
	fclose(FP);
	printf("Enter Product Name That You Want Find: ");
	scanf("%s",s);
	for(i=0;i<nt;i++)
		if(strcmp(s,pro[i].Name)==0)
			counter++;
			
	/*
	for(i=0,k=0;i<nt;i++){
		for(j=0;pro[i].Name[j]!=0 || s[j]!=0;j++)
			if(pro[i].Name[j]!=s[j])
				k=1;
		if(k==0){
			for(j=0;pro[i].Name[j];j++);
			for(i=0;s[i]!=0;i++);
			if(i!=j)
				k=1;
		}
		if(k==0)
			counter++;
	}
	*/
	if(counter==0)
			printf("This product there isnt\n");
		else
			printf("There is %d of this kind product\n",counter);
	//free(pro);
	Menu();
}
void Add(){
	struct Product *pro;
	int i,n,nt;
	FILE *FP;
	FILE *FPN;	//!
	FP=fopen("File.bin","ab");
	FPN=fopen("FilePN.bin","rb");	//!		//wrb??
	fread(&nt , sizeof(int) , 1 , FPN);	//!
	fclose(FPN);
	printf("nt=%d",nt); //*
	if(!FP){printf("couldn't open file\n");}
	printf("Enter Number of Products That You Want Enter:");
	scanf("%d",&n);
	nt+=n;	//!
	printf("nt=%d",nt); //*
	fopen("FilePN.bin","wb");
	fwrite(&nt,sizeof(int),1,FPN);	//!
	fclose(FPN);	//!
	pro=(struct Product*)malloc(n*sizeof(struct Product));
	for(i=0;i<n;i++){
		printf("Enter Details of Product Name %d:\n",i+1);
		printf("Enter Product Name: ");
		scanf("%s",pro[i].Name);
		printf("Enter Product Company Name: ");
		scanf("%s",pro[i].CompanyName);
		printf("Enter Product id: ");
		scanf("%d",&pro[i].Id);
		printf("Enter Product Price: ");
		scanf("%lf",&pro[i].Price);
		printf("Enter Product ExpirationDate: \n");
		printf("Enter Product ExpirationDate Day: ");
		scanf("%d",&pro[i].ExpirationDate.Day);
		printf("Enter Product ExpirationDate Month: ");
		scanf("%d",&pro[i].ExpirationDate.Month);
		printf("Enter Product ExpirationDate Year: ");
		scanf("%d",&pro[i].ExpirationDate.Year);
	}
	fwrite(pro,sizeof(struct Product),n,FP);
	fclose(FP);
	//free(pro);
	Menu();
}
void Show(){
	int nt,i;
	FILE *FP, *FPN;
	struct Product *pro;
	FP=fopen("File.bin","rb");
	FPN=fopen("FilePN.bin","rb");
	fread(&nt , sizeof(int) , 1 , FPN);
	printf("nt=%d\n",nt); //*
	pro=(struct Product*)malloc(nt*sizeof(struct Product));
	fread(pro, sizeof(struct Product), nt, FP);
	for(i=0;i<nt;i++){
		printf("Details of product %d \n",i+1);
		printf("Product Name: %s\n",pro[i].Name);
		printf("Product Company Name: %s\n",pro[i].CompanyName);
		printf("Product Price: %lf\n",pro[i].Price);
		printf("Product ExpirationDate: %d/%d/%d\n", pro[i].ExpirationDate.Year, pro[i].ExpirationDate.Month, pro[i].ExpirationDate.Day);
		printf("Product Id: %d\n",pro[i].Id);
	}
	fclose(FP);
	fclose(FPN);
	//free(pro);
	Menu();
}
