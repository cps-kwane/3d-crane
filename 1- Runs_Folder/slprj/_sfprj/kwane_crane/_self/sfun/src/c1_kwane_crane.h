#ifndef __c1_kwane_crane_h__
#define __c1_kwane_crane_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_kwane_craneInstanceStruct
#define typedef_SFc1_kwane_craneInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_S0_IDLE;
  uint8_T c1_tp_S1_Initialize;
  uint8_T c1_tp_S1_setpoints1;
  uint8_T c1_tp_S1_setup_pidy1;
  uint8_T c1_tp_S1_setup_pidy;
  uint8_T c1_tp_S2_Move_to_waypoint;
  uint8_T c1_tp_S3_log_stats_delay;
  uint8_T c1_tp_S4_checkifdone;
  uint8_T c1_tp_S5_done;
  uint8_T c1_is_active_c1_kwane_crane;
  uint8_T c1_is_c1_kwane_crane;
  uint8_T c1_is_active_S1_setpoints1;
  uint8_T c1_is_active_S1_setup_pidy1;
  uint8_T c1_is_active_S1_setup_pidy;
  real_T c1_finished;
  real_T c1_waypoints_reached_l;
  real_T c1_ylocal;
  real_T c1_index;
  real_T c1_xlocal;
  real_T c1_Kpa_l;
  real_T c1_tsy_l;
  real_T c1_Kix_l;
  real_T c1_ts;
  real_T c1_Kpx_l;
  real_T c1_Ki_l;
  real_T c1_Kpax_l;
  real_T c1_Kp_l;
  real_T c1_tsx_l;
  real_T c1_arrived;
  uint32_T c1_temporalCounter_i1;
  boolean_T c1_dataWrittenToVector[33];
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
  real_T *c1_xpos;
  boolean_T *c1_done;
  real_T *c1_kpax;
  real_T *c1_xref;
  real_T *c1_kpx;
  real_T (*c1_xwaypoints)[7];
  real_T (*c1_ywaypoints)[7];
  real_T *c1_start_course;
  real_T *c1_total_waypoints;
  real_T *c1_ypos;
  real_T *c1_kix;
  real_T *c1_yref;
  real_T *c1_Kpy;
  real_T *c1_Kiy;
  real_T *c1_Kpay;
  real_T *c1_waypoints_reached;
} SFc1_kwane_craneInstanceStruct;

#endif                                 /*typedef_SFc1_kwane_craneInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_kwane_crane_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_kwane_crane_get_check_sum(mxArray *plhs[]);
extern void c1_kwane_crane_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
