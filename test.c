#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BRAND_LEN 20
#define MAX_MODEL_LEN 20
#define MAX_NAME_LEN 20
#define MAX_PHONE_LEN 15
#define MAX_RECORDS 20

typedef enum {
    Warehouse,      // 入库状态
    Outbound,       // 出库状态
    Disassemble     // 拆解状态
} Status;



typedef struct {
    int recordId;                       // 记录编号
    char brand[MAX_BRAND_LEN];          // 手机品牌
    char model[MAX_MODEL_LEN];          // 手机型号
    int condition;                      // 新旧程度
    int isScreenBroken;                 // 屏幕是否破损
    char sellerName[MAX_NAME_LEN];      // 卖家姓名
    char sellerPhone[MAX_PHONE_LEN];    // 卖家电话
    Status status;                      // 当前状态
    char date[20];                      // 日期
    float price;                        // 价格
    char personnelName[MAX_NAME_LEN];   // 操作人员姓名
    int personnelId;                    // 操作人员工号
} PhoneRecord;



PhoneRecord records[MAX_RECORDS];       // 手机记录数组
int numRecords = 0;                     // 记录数量

int compareRecords(const void* a, const void* b) {
    PhoneRecord* recordA = (PhoneRecord*)a;
    PhoneRecord* recordB = (PhoneRecord*)b;
    return recordA->recordId - recordB->recordId;
}

void readRecordsFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        while (!feof(file)) {
            fscanf(file, "%d %s %s %d %d %s %s %d %s %f %s %d\n",
                &records[numRecords].recordId,
                records[numRecords].brand,
                records[numRecords].model,
                &records[numRecords].condition,
                &records[numRecords].isScreenBroken,
                records[numRecords].sellerName,
                records[numRecords].sellerPhone,
                (int*)&records[numRecords].status,
                records[numRecords].date,
                &records[numRecords].price,
                records[numRecords].personnelName,
                &records[numRecords].personnelId
            );
            numRecords++;
        }
        fclose(file);
    }
}

void saveRecordsToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < numRecords; i++) {
            fprintf(file, "%d %s %s %d %d %s %s %d %s %.2f %s %d\n",
                records[i].recordId,
                records[i].brand,
                records[i].model,
                records[i].condition,
                records[i].isScreenBroken,
                records[i].sellerName,
                records[i].sellerPhone,
                records[i].status,
                records[i].date,
                records[i].price,
                records[i].personnelName,
                records[i].personnelId
            );
        }
        fclose(file);
    }
}

//添加新手机信息
void addRecord() {
    PhoneRecord newRecord;
    printf("请输入新记录的信息：\n");
    printf("记录编号: ");
    scanf("%d", &newRecord.recordId);

    // 检查记录编号是否重复
    for (int i = 0; i < numRecords; i++) {
        if (records[i].recordId == newRecord.recordId) {
            printf("错误：记录编号已存在！\n");
            return;
        }
    }

    printf("手机品牌: ");
    scanf("%s", newRecord.brand);

    printf("手机型号: ");
    scanf("%s", newRecord.model);

    printf("新旧程度(1-10): ");
    scanf("%d", &newRecord.condition);

    printf("屏幕是否破损(0-否, 1-是): ");
    scanf("%d", &newRecord.isScreenBroken);

    printf("卖家姓名: ");
    scanf("%s", newRecord.sellerName);

    printf("卖家电话: ");
    scanf("%s", newRecord.sellerPhone);

    printf("当前状态 (0-入库, 1-出库, 2-拆解): ");
    scanf("%d", (int*)&newRecord.status);

    printf("日期 (YYYY/MM/DD): ");
    scanf("%s", newRecord.date);

    printf("价格: ");
    scanf("%f", &newRecord.price);

    printf("操作人员姓名: ");
    scanf("%s", newRecord.personnelName);

    printf("操作人员工号: ");
    scanf("%d", &newRecord.personnelId);

    records[numRecords] = newRecord;
    numRecords++;
    printf("成功添加新记录！\n");
}

//打印新手机信息
void displayRecords() {
    printf("编号\t品牌\t型号\t新旧程度\t屏幕破损\t卖家姓名\t卖家电话\t当前状态\t日期\t\t价格\t操作人员姓名\t操作人员工号\n");
    for (int i = 0; i < numRecords; i++) {
        printf("%d\t\t%s\t%s\t%d\t\t%s\t\t%s\t\t%d\t\t%s\t%.2f\t%s\t\t%d\n",
            records[i].recordId,
            records[i].brand,
            records[i].model,
            records[i].condition,
            records[i].isScreenBroken ? "是" : "否",
            records[i].sellerName,
            records[i].sellerPhone,
            records[i].status,
            records[i].date,
            records[i].price,
            records[i].personnelName,
            records[i].personnelId
        );
    }
}


//组合查询手机信息
void printRecord(PhoneRecord record) {
    printf("手机品牌: %s\n", record.brand);
    printf("手机型号：%s\n",record.model);
    printf("新旧程度: %d\n", record.condition);
    printf("屏幕状况: %s\n", record.isScreenBroken ? "已破损" : "未破损");

    printf("----------------------------\n");
}


//组合查询
void searchByCombination() {
    char brand[50];
    int condition;
    int isScreenBroken;

    printf("请输入手机品牌: ");
    scanf("%s", brand);
    printf("请输入新旧程度(1-10): ");
    scanf("%d", &condition);
    printf("请输入屏幕状况(0-未破损，1-已破损): ");
    scanf("%d", &isScreenBroken);

    printf("查询结果:\n");
    for (int i = 0; i < numRecords; i++) {
        if (strcmp(records[i].brand, brand) == 0 &&
            records[i].condition == condition &&
            records[i].isScreenBroken == isScreenBroken) {
            printRecord(records[i]);
        }
    }
}


//查询手机
void searchByCondition() {
    int condition;
    printf("请选择查询条件:\n");
    printf("1. 按手机品牌查询\n");
    printf("2. 按新旧程度查询\n");
    printf("3. 按屏幕状况查询\n");
    printf("4. 组合查询\n");
    printf("请输入选项: ");
    scanf("%d", &condition);

    switch (condition) {
    case 1: {
        char brand[50];
        printf("请输入手机品牌: ");
        scanf("%s", brand);
        printf("----------------------------\n");


        printf("查询结果:\n");
        for (int i = 0; i < numRecords; i++) {
            if (strcmp(records[i].brand, brand) == 0) {
                printRecord(records[i]);
            }
        }
        break;
    }
    case 2: {
        int condition;
        printf("请输入新旧程度(1-10): ");
        scanf("%d", &condition);
        printf("查询结果:\n");
        for (int i = 0; i < numRecords; i++) {
            if (records[i].condition == condition) {
                printRecord(records[i]);
            }
        }
        break;
    }
    case 3: {
        int isScreenBroken;
        printf("请输入屏幕状况(0-未破损，1-已破损): ");
        scanf("%d", &isScreenBroken);
        printf("查询结果:\n");
        for (int i = 0; i < numRecords; i++) {
            if (records[i].isScreenBroken == isScreenBroken) {
                printRecord(records[i]);
            }
        }
        break;
    }
    case 4:
        searchByCombination();
        break;
    default:
        printf("错误的选项！\n");
        break;
    }
}



// 修改信息
/*void modifyRecord(int recordId,PhoneRecord* records,int numRecords) {
    int found = 0;

    for (int i = 0; i < numRecords; i++) {
        if (records[i].recordId == recordId) {
            found = 1;

            printf("请输入新的手机品牌: ");
            scanf("%s", records[i].brand);

            printf("请输入新的手机型号: ");
            scanf("%s", records[i].model);

            printf("请输入新的新旧程度: ");
            scanf("%d", &records[i].condition);

            printf("请输入屏幕是否破损 (0表示未破损，1表示破损): ");
            scanf("%d", &records[i].isScreenBroken);

            printf("请输入新的卖家姓名: ");
            scanf("%s", records[i].sellerName);

            printf("请输入新的卖家电话: ");
            scanf("%s", records[i].sellerPhone);

            printf("请输入新的日期: ");
            scanf("%s", records[i].date);

            printf("请输入新的价格: ");
            scanf("%f", &records[i].price);

            printf("请输入新的操作人员姓名: ");
            scanf("%s", records[i].personnelName);

            printf("请输入新的操作人员工号: ");
            scanf("%d", &records[i].personnelId);

            saveRecordsToFile("data.txt");
            printf("记录已成功修改！\n");
            break;
        }
    }

    if (!found) {
        printf("找不到指定的记录！\n");
    }
}*/
/*void modifyRecord(int recordId, char* brand, char* model, int condition, int isScreenBroken, char* sellerName, char* sellerPhone, Status status, char* date, float price, char* personnelName, int personnelId) {
    for (int i = 0; i < numRecords; i++) {
        if (records[i].recordId == recordId) {
            // Modify the fields of the PhoneRecord
            strcpy(records[i].brand, brand);
            strcpy(records[i].model, model);
            records[i].condition = condition;
            records[i].isScreenBroken = isScreenBroken;
            strcpy(records[i].sellerName, sellerName);
            strcpy(records[i].sellerPhone, sellerPhone);
            records[i].status = status;
            strcpy(records[i].date, date);
            records[i].price = price;
            strcpy(records[i].personnelName, personnelName);
            records[i].personnelId = personnelId;
            return;
        }
    }
    // If the record is not found, print an error message
    printf("Record with ID %d not found.\n", recordId);
}*/



//删除信息
void deleteRecord(int recordId) {
    for (int i = 0; i < numRecords; i++) {
        if (records[i].recordId == recordId) {
            // Shift all records after the deleted record one position to the left
            for (int j = i + 1; j < numRecords; j++) {
                records[j - 1] = records[j];
            }
            // Decrement the number of records and return
            numRecords--;
            return;
        }
    }
    // If the record is not found, print an error message
    printf("Record with ID %d not found.\n", recordId);
}



float calculateRecyclingCost() {
    float totalCost = 0.0;

    for (int i = 0; i < numRecords; i++) {
        if (records[i].status == 2)//如果被拆解 计算成本
        {
            // Calculate the recycling cost based on the condition and screen status
            float conditionFactor = records[i].condition == 0 ? 0.5 : 1.0;//当前状态 新旧程度 如果全新系数为1
            float screenFactor = records[i].isScreenBroken ==0 ? 0.8 : 1.0;//屏幕破损程度 如果破损 系数为0.8
            float cost = records[i].price * conditionFactor * screenFactor;

            totalCost += cost;
        }
    }

    printf("%.2f",totalCost);

    return totalCost;
}

int main() {
    readRecordsFromFile("data.txt");

    int choice;
    do {
        printf("\n手机回收与销售管理系统\n");
        printf("***************************\n");
        printf("***************************\n");
        printf("*****1. 添加记录      *****\n");
        printf("*****2. 显示记录      *****\n");
        printf("*****3. 查询记录      *****\n");
        printf("*****4. 排序记录      *****\n");
        printf("*****5. 保存记录到文件*****\n");
        printf("*****6. 修改记录      *****\n");
        printf("*****7. 删除数据      *****\n");
        printf("*****8. 统计回收成本  *****\n");
        printf("*****0. 退出          *****\n");
        printf("***************************\n");
        printf("***************************\n");
        printf("请输入选项: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            displayRecords();
            break;
        case 3:
            searchByCondition();
            break;
        case 4:
            qsort(records, numRecords, sizeof(PhoneRecord), compareRecords);
            printf("成功排序记录！\n");
            break;
        case 5:
            saveRecordsToFile("data.txt");
            printf("成功保存记录到文件！\n");
            break;
        /*case 6:
            modifyRecord();*/
        case 7:
            deleteRecord();
            break;
        case 8:
            calculateRecyclingCost();
            break;
        case 0:
            printf("再见！\n");
            break;
        default:
            printf("错误的选项！\n");
            break;
        }
    } while (choice != 0);

    return 0;
}


