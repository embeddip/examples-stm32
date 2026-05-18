/* USER CODE BEGIN Includes */
#include <math.h>
/* USER CODE END Includes */

/* USER CODE BEGIN 0 */
float data[1000];
/* USER CODE END 0 */

/* USER CODE BEGIN 2 */
uint32_t executionCycles;
tic();
for (uint32_t i = 0; i < 1000; i++){
  data[i] = M_PI * M_E * i;
}
executionCycles = toc();
/* USER CODE END 2 */
