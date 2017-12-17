/* Include files */

#include "kwane_crane_sfun.h"
#include "c1_kwane_crane.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "kwane_crane_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_S0_IDLE                  ((uint8_T)1U)
#define c1_IN_S1_Initialize            ((uint8_T)2U)
#define c1_IN_S2_Move_to_waypoint      ((uint8_T)3U)
#define c1_IN_S3_log_stats_delay       ((uint8_T)4U)
#define c1_IN_S4_checkifdone           ((uint8_T)5U)
#define c1_IN_S5_done                  ((uint8_T)6U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_d_debug_family_names[10] = { "temp0", "temp", "nargin",
  "nargout", "ycurrent", "ydest", "Ki", "Kpa", "Kp", "tsy" };

static const char * c1_e_debug_family_names[4] = { "nargin", "nargout",
  "ycurrent", "ydest" };

static const char * c1_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_g_debug_family_names[10] = { "temp0", "temp", "nargin",
  "nargout", "xcurrent", "xdest", "Kix", "Kpax", "Kpx", "tsx" };

static const char * c1_h_debug_family_names[4] = { "nargin", "nargout",
  "xcurrent", "xdest" };

static const char * c1_i_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_j_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_k_debug_family_names[6] = { "nargin", "nargout",
  "currentx", "currenty", "xdest", "ydest" };

static const char * c1_l_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_m_debug_family_names[4] = { "nargin", "nargout", "count",
  "total" };

static const char * c1_n_debug_family_names[2] = { "nargin", "nargout" };

static const char * c1_o_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c1_p_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c1_q_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c1_r_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void initialize_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void initialize_params_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void enable_c1_kwane_crane(SFc1_kwane_craneInstanceStruct *chartInstance);
static void disable_c1_kwane_crane(SFc1_kwane_craneInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_kwane_crane
  (SFc1_kwane_craneInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_kwane_crane
  (SFc1_kwane_craneInstanceStruct *chartInstance);
static void set_sim_state_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void c1_set_sim_state_side_effects_c1_kwane_crane
  (SFc1_kwane_craneInstanceStruct *chartInstance);
static void finalize_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void sf_gateway_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void mdl_start_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void c1_chartstep_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void initSimStructsc1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void c1_enter_internal_S1_Initialize(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void c1_S1_Initialize(SFc1_kwane_craneInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct *chartInstance,
  const mxArray *c1_nargout, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static boolean_T c1_c_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_sf_internal_predicateOutput, const char_T
  *c1_identifier);
static boolean_T c1_d_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_setpidy(SFc1_kwane_craneInstanceStruct *chartInstance, real_T
  c1_ycurrent, real_T c1_ydest, real_T *c1_Ki, real_T *c1_Kpa, real_T *c1_Kp,
  real_T *c1_tsy);
static void c1_setpidx(SFc1_kwane_craneInstanceStruct *chartInstance, real_T
  c1_xcurrent, real_T c1_xdest, real_T *c1_Kix, real_T *c1_Kpax, real_T *c1_Kpx,
  real_T *c1_tsx);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_b_tp_S0_IDLE, const char_T *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint32_T c1_h_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_b_temporalCounter_i1, const char_T
  *c1_identifier);
static uint32_T c1_i_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_j_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct *chartInstance,
  const mxArray *c1_b_dataWrittenToVector, const char_T *c1_identifier,
  boolean_T c1_y[33]);
static void c1_k_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T c1_y[33]);
static const mxArray *c1_l_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier);
static const mxArray *c1_m_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc1_kwane_craneInstanceStruct
  *chartInstance, int32_T c1_ssid);
static void c1_init_sf_message_store_memory(SFc1_kwane_craneInstanceStruct
  *chartInstance);
static void init_dsm_address_info(SFc1_kwane_craneInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_kwane_craneInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_kwane_crane(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  chartInstance->c1_tp_S0_IDLE = 0U;
  chartInstance->c1_tp_S1_Initialize = 0U;
  chartInstance->c1_is_active_S1_setpoints1 = 0U;
  chartInstance->c1_tp_S1_setpoints1 = 0U;
  chartInstance->c1_is_active_S1_setup_pidy = 0U;
  chartInstance->c1_tp_S1_setup_pidy = 0U;
  chartInstance->c1_is_active_S1_setup_pidy1 = 0U;
  chartInstance->c1_tp_S1_setup_pidy1 = 0U;
  chartInstance->c1_tp_S2_Move_to_waypoint = 0U;
  chartInstance->c1_tp_S3_log_stats_delay = 0U;
  chartInstance->c1_temporalCounter_i1 = 0U;
  chartInstance->c1_tp_S4_checkifdone = 0U;
  chartInstance->c1_tp_S5_done = 0U;
  chartInstance->c1_is_active_c1_kwane_crane = 0U;
  chartInstance->c1_is_c1_kwane_crane = c1_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_kwane_crane(SFc1_kwane_craneInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_kwane_crane(SFc1_kwane_craneInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_kwane_crane
  (SFc1_kwane_craneInstanceStruct *chartInstance)
{
  uint32_T c1_prevAniVal;
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c1_is_active_c1_kwane_crane == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S0_IDLE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S1_Initialize) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_S1_setpoints1 == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_S1_setup_pidy1 == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_S1_setup_pidy == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S2_Move_to_waypoint) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S3_log_stats_delay) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S4_checkifdone) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S5_done) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c1_kwane_crane
  (SFc1_kwane_craneInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  boolean_T c1_d_hoistedGlobal;
  const mxArray *c1_e_y = NULL;
  real_T c1_e_hoistedGlobal;
  const mxArray *c1_f_y = NULL;
  real_T c1_f_hoistedGlobal;
  const mxArray *c1_g_y = NULL;
  real_T c1_g_hoistedGlobal;
  const mxArray *c1_h_y = NULL;
  real_T c1_h_hoistedGlobal;
  const mxArray *c1_i_y = NULL;
  real_T c1_i_hoistedGlobal;
  const mxArray *c1_j_y = NULL;
  real_T c1_j_hoistedGlobal;
  const mxArray *c1_k_y = NULL;
  real_T c1_k_hoistedGlobal;
  const mxArray *c1_l_y = NULL;
  real_T c1_l_hoistedGlobal;
  const mxArray *c1_m_y = NULL;
  real_T c1_m_hoistedGlobal;
  const mxArray *c1_n_y = NULL;
  real_T c1_n_hoistedGlobal;
  const mxArray *c1_o_y = NULL;
  real_T c1_o_hoistedGlobal;
  const mxArray *c1_p_y = NULL;
  real_T c1_p_hoistedGlobal;
  const mxArray *c1_q_y = NULL;
  real_T c1_q_hoistedGlobal;
  const mxArray *c1_r_y = NULL;
  real_T c1_r_hoistedGlobal;
  const mxArray *c1_s_y = NULL;
  real_T c1_s_hoistedGlobal;
  const mxArray *c1_t_y = NULL;
  real_T c1_t_hoistedGlobal;
  const mxArray *c1_u_y = NULL;
  real_T c1_u_hoistedGlobal;
  const mxArray *c1_v_y = NULL;
  real_T c1_v_hoistedGlobal;
  const mxArray *c1_w_y = NULL;
  real_T c1_w_hoistedGlobal;
  const mxArray *c1_x_y = NULL;
  real_T c1_x_hoistedGlobal;
  const mxArray *c1_y_y = NULL;
  real_T c1_y_hoistedGlobal;
  const mxArray *c1_ab_y = NULL;
  uint8_T c1_ab_hoistedGlobal;
  const mxArray *c1_bb_y = NULL;
  uint8_T c1_bb_hoistedGlobal;
  const mxArray *c1_cb_y = NULL;
  uint8_T c1_cb_hoistedGlobal;
  const mxArray *c1_db_y = NULL;
  uint8_T c1_db_hoistedGlobal;
  const mxArray *c1_eb_y = NULL;
  uint8_T c1_eb_hoistedGlobal;
  const mxArray *c1_fb_y = NULL;
  uint32_T c1_fb_hoistedGlobal;
  const mxArray *c1_gb_y = NULL;
  const mxArray *c1_hb_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(32, 1), false);
  c1_hoistedGlobal = *chartInstance->c1_Kiy;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *chartInstance->c1_Kpay;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *chartInstance->c1_Kpy;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *chartInstance->c1_done;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_hoistedGlobal, 11, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = *chartInstance->c1_kix;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = *chartInstance->c1_kpax;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = *chartInstance->c1_kpx;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_h_hoistedGlobal = *chartInstance->c1_waypoints_reached;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_i_hoistedGlobal = *chartInstance->c1_xref;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_j_hoistedGlobal = *chartInstance->c1_yref;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_k_hoistedGlobal = chartInstance->c1_Ki_l;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_k_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_l_hoistedGlobal = chartInstance->c1_Kix_l;
  c1_m_y = NULL;
  sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_l_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 11, c1_m_y);
  c1_m_hoistedGlobal = chartInstance->c1_Kp_l;
  c1_n_y = NULL;
  sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_m_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 12, c1_n_y);
  c1_n_hoistedGlobal = chartInstance->c1_Kpa_l;
  c1_o_y = NULL;
  sf_mex_assign(&c1_o_y, sf_mex_create("y", &c1_n_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 13, c1_o_y);
  c1_o_hoistedGlobal = chartInstance->c1_Kpax_l;
  c1_p_y = NULL;
  sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_o_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 14, c1_p_y);
  c1_p_hoistedGlobal = chartInstance->c1_Kpx_l;
  c1_q_y = NULL;
  sf_mex_assign(&c1_q_y, sf_mex_create("y", &c1_p_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 15, c1_q_y);
  c1_q_hoistedGlobal = chartInstance->c1_arrived;
  c1_r_y = NULL;
  sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_q_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 16, c1_r_y);
  c1_r_hoistedGlobal = chartInstance->c1_finished;
  c1_s_y = NULL;
  sf_mex_assign(&c1_s_y, sf_mex_create("y", &c1_r_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 17, c1_s_y);
  c1_s_hoistedGlobal = chartInstance->c1_index;
  c1_t_y = NULL;
  sf_mex_assign(&c1_t_y, sf_mex_create("y", &c1_s_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 18, c1_t_y);
  c1_t_hoistedGlobal = chartInstance->c1_ts;
  c1_u_y = NULL;
  sf_mex_assign(&c1_u_y, sf_mex_create("y", &c1_t_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 19, c1_u_y);
  c1_u_hoistedGlobal = chartInstance->c1_tsx_l;
  c1_v_y = NULL;
  sf_mex_assign(&c1_v_y, sf_mex_create("y", &c1_u_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 20, c1_v_y);
  c1_v_hoistedGlobal = chartInstance->c1_tsy_l;
  c1_w_y = NULL;
  sf_mex_assign(&c1_w_y, sf_mex_create("y", &c1_v_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 21, c1_w_y);
  c1_w_hoistedGlobal = chartInstance->c1_waypoints_reached_l;
  c1_x_y = NULL;
  sf_mex_assign(&c1_x_y, sf_mex_create("y", &c1_w_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 22, c1_x_y);
  c1_x_hoistedGlobal = chartInstance->c1_xlocal;
  c1_y_y = NULL;
  sf_mex_assign(&c1_y_y, sf_mex_create("y", &c1_x_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 23, c1_y_y);
  c1_y_hoistedGlobal = chartInstance->c1_ylocal;
  c1_ab_y = NULL;
  sf_mex_assign(&c1_ab_y, sf_mex_create("y", &c1_y_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 24, c1_ab_y);
  c1_ab_hoistedGlobal = chartInstance->c1_is_active_c1_kwane_crane;
  c1_bb_y = NULL;
  sf_mex_assign(&c1_bb_y, sf_mex_create("y", &c1_ab_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 25, c1_bb_y);
  c1_bb_hoistedGlobal = chartInstance->c1_is_active_S1_setup_pidy1;
  c1_cb_y = NULL;
  sf_mex_assign(&c1_cb_y, sf_mex_create("y", &c1_bb_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 26, c1_cb_y);
  c1_cb_hoistedGlobal = chartInstance->c1_is_active_S1_setpoints1;
  c1_db_y = NULL;
  sf_mex_assign(&c1_db_y, sf_mex_create("y", &c1_cb_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 27, c1_db_y);
  c1_db_hoistedGlobal = chartInstance->c1_is_active_S1_setup_pidy;
  c1_eb_y = NULL;
  sf_mex_assign(&c1_eb_y, sf_mex_create("y", &c1_db_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 28, c1_eb_y);
  c1_eb_hoistedGlobal = chartInstance->c1_is_c1_kwane_crane;
  c1_fb_y = NULL;
  sf_mex_assign(&c1_fb_y, sf_mex_create("y", &c1_eb_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 29, c1_fb_y);
  c1_fb_hoistedGlobal = chartInstance->c1_temporalCounter_i1;
  c1_gb_y = NULL;
  sf_mex_assign(&c1_gb_y, sf_mex_create("y", &c1_fb_hoistedGlobal, 7, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 30, c1_gb_y);
  c1_hb_y = NULL;
  sf_mex_assign(&c1_hb_y, sf_mex_create("y",
    chartInstance->c1_dataWrittenToVector, 11, 0U, 1U, 0U, 1, 33), false);
  sf_mex_setcell(c1_y, 31, c1_hb_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  boolean_T c1_bv0[33];
  int32_T c1_i0;
  c1_u = sf_mex_dup(c1_st);
  *chartInstance->c1_Kiy = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kiy", c1_u, 0)), "Kiy");
  *chartInstance->c1_Kpay = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kpay", c1_u, 1)), "Kpay");
  *chartInstance->c1_Kpy = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kpy", c1_u, 2)), "Kpy");
  *chartInstance->c1_done = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("done", c1_u, 3)), "done");
  *chartInstance->c1_kix = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("kix", c1_u, 4)), "kix");
  *chartInstance->c1_kpax = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("kpax", c1_u, 5)), "kpax");
  *chartInstance->c1_kpx = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("kpx", c1_u, 6)), "kpx");
  *chartInstance->c1_waypoints_reached = c1_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("waypoints_reached", c1_u, 7)),
    "waypoints_reached");
  *chartInstance->c1_xref = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("xref", c1_u, 8)), "xref");
  *chartInstance->c1_yref = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("yref", c1_u, 9)), "yref");
  chartInstance->c1_Ki_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Ki_l", c1_u, 10)), "Ki_l");
  chartInstance->c1_Kix_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kix_l", c1_u, 11)), "Kix_l");
  chartInstance->c1_Kp_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kp_l", c1_u, 12)), "Kp_l");
  chartInstance->c1_Kpa_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kpa_l", c1_u, 13)), "Kpa_l");
  chartInstance->c1_Kpax_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kpax_l", c1_u, 14)), "Kpax_l");
  chartInstance->c1_Kpx_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("Kpx_l", c1_u, 15)), "Kpx_l");
  chartInstance->c1_arrived = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("arrived", c1_u, 16)), "arrived");
  chartInstance->c1_finished = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("finished", c1_u, 17)), "finished");
  chartInstance->c1_index = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("index", c1_u, 18)), "index");
  chartInstance->c1_ts = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ts", c1_u, 19)), "ts");
  chartInstance->c1_tsx_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("tsx_l", c1_u, 20)), "tsx_l");
  chartInstance->c1_tsy_l = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("tsy_l", c1_u, 21)), "tsy_l");
  chartInstance->c1_waypoints_reached_l = c1_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("waypoints_reached_l", c1_u, 22)),
    "waypoints_reached_l");
  chartInstance->c1_xlocal = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("xlocal", c1_u, 23)), "xlocal");
  chartInstance->c1_ylocal = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("ylocal", c1_u, 24)), "ylocal");
  chartInstance->c1_is_active_c1_kwane_crane = c1_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c1_kwane_crane", c1_u,
       25)), "is_active_c1_kwane_crane");
  chartInstance->c1_is_active_S1_setup_pidy1 = c1_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_S1_setup_pidy1", c1_u,
       26)), "is_active_S1_setup_pidy1");
  chartInstance->c1_is_active_S1_setpoints1 = c1_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_S1_setpoints1", c1_u,
       27)), "is_active_S1_setpoints1");
  chartInstance->c1_is_active_S1_setup_pidy = c1_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_S1_setup_pidy", c1_u,
       28)), "is_active_S1_setup_pidy");
  chartInstance->c1_is_c1_kwane_crane = c1_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_c1_kwane_crane", c1_u, 29)),
    "is_c1_kwane_crane");
  chartInstance->c1_temporalCounter_i1 = c1_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("temporalCounter_i1", c1_u, 30)),
    "temporalCounter_i1");
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "dataWrittenToVector", c1_u, 31)), "dataWrittenToVector", c1_bv0);
  for (c1_i0 = 0; c1_i0 < 33; c1_i0++) {
    chartInstance->c1_dataWrittenToVector[c1_i0] = c1_bv0[c1_i0];
  }

  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(
    "setSimStateSideEffectsInfo", c1_u, 32)), "setSimStateSideEffectsInfo"),
                true);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_kwane_crane(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_kwane_crane
  (SFc1_kwane_craneInstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    chartInstance->c1_tp_S0_IDLE = (uint8_T)(chartInstance->c1_is_c1_kwane_crane
      == c1_IN_S0_IDLE);
    chartInstance->c1_tp_S1_Initialize = (uint8_T)
      (chartInstance->c1_is_c1_kwane_crane == c1_IN_S1_Initialize);
    chartInstance->c1_tp_S1_setpoints1 = (uint8_T)
      (chartInstance->c1_is_active_S1_setpoints1 == 1U);
    chartInstance->c1_tp_S1_setup_pidy1 = (uint8_T)
      (chartInstance->c1_is_active_S1_setup_pidy1 == 1U);
    chartInstance->c1_tp_S1_setup_pidy = (uint8_T)
      (chartInstance->c1_is_active_S1_setup_pidy == 1U);
    chartInstance->c1_tp_S2_Move_to_waypoint = (uint8_T)
      (chartInstance->c1_is_c1_kwane_crane == c1_IN_S2_Move_to_waypoint);
    if (chartInstance->c1_is_c1_kwane_crane == c1_IN_S3_log_stats_delay) {
      chartInstance->c1_tp_S3_log_stats_delay = 1U;
      if (sf_mex_sub(chartInstance->c1_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 8) == 0.0) {
        chartInstance->c1_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c1_tp_S3_log_stats_delay = 0U;
    }

    chartInstance->c1_tp_S4_checkifdone = (uint8_T)
      (chartInstance->c1_is_c1_kwane_crane == c1_IN_S4_checkifdone);
    chartInstance->c1_tp_S5_done = (uint8_T)(chartInstance->c1_is_c1_kwane_crane
      == c1_IN_S5_done);
    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_gateway_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  int32_T c1_i1;
  int32_T c1_i2;
  c1_set_sim_state_side_effects_c1_kwane_crane(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c1_temporalCounter_i1 < MAX_uint32_T) {
    chartInstance->c1_temporalCounter_i1++;
  }

  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_ypos, 20U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_total_waypoints, 19U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_start_course, 18U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  for (c1_i1 = 0; c1_i1 < 7; c1_i1++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_ywaypoints)[c1_i1], 17U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i2 = 0; c1_i2 < 7; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_xwaypoints)[c1_i2], 16U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_xpos, 15U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_kwane_crane(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_kwane_craneMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  c1_init_sf_message_store_memory(chartInstance);
}

static void c1_chartstep_c1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  uint32_T c1_debug_family_var_map[3];
  real_T c1_nargin = 0.0;
  real_T c1_b_nargin = 0.0;
  real_T c1_c_nargin = 0.0;
  real_T c1_nargout = 1.0;
  real_T c1_b_nargout = 1.0;
  real_T c1_c_nargout = 1.0;
  boolean_T c1_out;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  uint32_T c1_b_debug_family_var_map[2];
  real_T c1_d_nargin = 0.0;
  real_T c1_d_nargout = 0.0;
  real_T c1_e_nargin = 0.0;
  real_T c1_f_nargin = 0.0;
  real_T c1_e_nargout = 0.0;
  real_T c1_f_nargout = 1.0;
  boolean_T c1_d_out;
  real_T c1_g_nargin = 0.0;
  real_T c1_hoistedGlobal;
  real_T c1_g_nargout = 0.0;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_hoistedGlobal;
  real_T c1_d_hoistedGlobal;
  real_T c1_e_hoistedGlobal;
  real_T c1_currentx;
  real_T c1_f_hoistedGlobal;
  real_T c1_currenty;
  real_T c1_count;
  real_T c1_xdest;
  real_T c1_total;
  real_T c1_ydest;
  uint32_T c1_c_debug_family_var_map[4];
  uint32_T c1_d_debug_family_var_map[6];
  real_T c1_h_nargin = 0.0;
  real_T c1_i_nargin = 2.0;
  real_T c1_h_nargout = 0.0;
  real_T c1_j_nargin = 4.0;
  real_T c1_i_nargout = 0.0;
  real_T c1_j_nargout = 0.0;
  boolean_T c1_sf_internal_predicateOutput;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_y;
  real_T c1_g_hoistedGlobal;
  const mxArray *c1_b_y = NULL;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_h_hoistedGlobal;
  real_T c1_f_x;
  const mxArray *c1_c_y = NULL;
  boolean_T c1_b_sf_internal_predicateOutput;
  real_T c1_d_y;
  boolean_T guard1 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  if (chartInstance->c1_is_active_c1_kwane_crane == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_active_c1_kwane_crane = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_kwane_crane = c1_IN_S0_IDLE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_S0_IDLE = 1U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_debug_family_names,
      c1_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargin, 0U, c1_sf_marshallOut,
      c1_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargout, 1U, c1_sf_marshallOut,
      c1_sf_marshallIn);
    chartInstance->c1_xlocal = 0.0;
    chartInstance->c1_dataWrittenToVector[14U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_xlocal, 13U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_ylocal = 0.0;
    chartInstance->c1_dataWrittenToVector[12U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_ylocal, 14U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    *chartInstance->c1_done = false;
    chartInstance->c1_dataWrittenToVector[0U] = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_done, 21U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_index = 1.0;
    chartInstance->c1_dataWrittenToVector[13U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_index, 8U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_Kp_l = 0.0;
    chartInstance->c1_dataWrittenToVector[22U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kp_l, 2U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_Ki_l = 0.0;
    chartInstance->c1_dataWrittenToVector[20U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Ki_l, 0U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_Kpa_l = 0.0;
    chartInstance->c1_dataWrittenToVector[15U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kpa_l, 3U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_Kix_l = 0.0;
    chartInstance->c1_dataWrittenToVector[17U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kix_l, 1U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_Kpx_l = 0.0;
    chartInstance->c1_dataWrittenToVector[19U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kpx_l, 5U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_Kpax_l = 0.0;
    chartInstance->c1_dataWrittenToVector[21U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kpax_l, 4U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_tsy_l = 0.0;
    chartInstance->c1_dataWrittenToVector[16U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_tsy_l, 11U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_tsx_l = 0.0;
    chartInstance->c1_dataWrittenToVector[23U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_tsx_l, 10U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_waypoints_reached_l = 0.0;
    chartInstance->c1_dataWrittenToVector[11U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_waypoints_reached_l, 12U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    chartInstance->c1_ts = 0.0;
    chartInstance->c1_dataWrittenToVector[18U] = true;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_ts, 9U, 4U, 0U,
                          chartInstance->c1_sfEvent, false);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    switch (chartInstance->c1_is_c1_kwane_crane) {
     case c1_IN_S0_IDLE:
      CV_CHART_EVAL(0, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   chartInstance->c1_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c1_o_debug_family_names,
        c1_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 0U, c1_sf_marshallOut,
        c1_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 1U, c1_sf_marshallOut,
        c1_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_out, 2U, c1_b_sf_marshallOut,
        c1_b_sf_marshallIn);
      c1_out = CV_EML_IF(1, 0, 0, CV_RELATIONAL_EVAL(5U, 1U, 0,
        *chartInstance->c1_start_course, 1.0, -1, 0U,
        *chartInstance->c1_start_course == 1.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c1_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_S0_IDLE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_kwane_crane = c1_IN_S1_Initialize;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_S1_Initialize = 1U;
        c1_enter_internal_S1_Initialize(chartInstance);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_S1_Initialize:
      CV_CHART_EVAL(0, 0, 2);
      c1_S1_Initialize(chartInstance);
      break;

     case c1_IN_S2_Move_to_waypoint:
      CV_CHART_EVAL(0, 0, 3);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_S2_Move_to_waypoint = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_c1_kwane_crane = c1_IN_S3_log_stats_delay;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      chartInstance->c1_temporalCounter_i1 = 0U;
      chartInstance->c1_tp_S3_log_stats_delay = 1U;
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_S3_log_stats_delay:
      CV_CHART_EVAL(0, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U,
                   chartInstance->c1_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c1_q_debug_family_names,
        c1_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargin, 0U, c1_sf_marshallOut,
        c1_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargout, 1U, c1_sf_marshallOut,
        c1_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_out, 2U, c1_b_sf_marshallOut,
        c1_b_sf_marshallIn);
      if (!chartInstance->c1_dataWrittenToVector[18U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(9U, 5U, 18U, chartInstance->c1_sfEvent,
          false);
      }

      c1_b_out = CV_EML_IF(18, 0, 0, chartInstance->c1_temporalCounter_i1 >=
                           (uint32_T)muDoubleScalarCeil(chartInstance->c1_ts /
        0.01 - 1.0E-10));
      _SFD_SYMBOL_SCOPE_POP();
      if (c1_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_S3_log_stats_delay = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_kwane_crane = c1_IN_S4_checkifdone;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_S4_checkifdone = 1U;
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_l_debug_family_names,
          c1_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g_nargin, 0U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_g_nargout, 1U,
          c1_sf_marshallOut, c1_sf_marshallIn);
        if (!chartInstance->c1_dataWrittenToVector[13U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U, 4U, 7U,
            chartInstance->c1_sfEvent, false);
        }

        c1_e_hoistedGlobal = chartInstance->c1_index;
        c1_f_hoistedGlobal = *chartInstance->c1_total_waypoints;
        c1_count = c1_e_hoistedGlobal;
        c1_total = c1_f_hoistedGlobal;
        _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_m_debug_family_names,
          c1_c_debug_family_var_map);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                     chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_i_nargin, 0U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_i_nargout, 1U,
          c1_sf_marshallOut, c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_count, 2U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_total, 3U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c1_sfEvent);
        c1_sf_internal_predicateOutput = CV_EML_IF(8, 0, 0, c1_count > c1_total);
        if (c1_sf_internal_predicateOutput) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
          chartInstance->c1_finished = 1.0;
          chartInstance->c1_dataWrittenToVector[4U] = true;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_finished, 7U, 5U, 11U,
                                chartInstance->c1_sfEvent, false);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
          chartInstance->c1_finished = 0.0;
          chartInstance->c1_dataWrittenToVector[4U] = true;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_finished, 7U, 5U, 9U,
                                chartInstance->c1_sfEvent, false);
          if (!chartInstance->c1_dataWrittenToVector[4U]) {
            _SFD_DATA_READ_BEFORE_WRITE_ERROR(7U, 5U, 9U,
              chartInstance->c1_sfEvent, false);
          }

          sf_mex_printf("%s =\\n", "finished");
          c1_h_hoistedGlobal = chartInstance->c1_finished;
          c1_c_y = NULL;
          sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_h_hoistedGlobal, 0, 0U,
            0U, 0U, 0), false);
          sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14,
                            c1_c_y);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_POP();
        _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c1_sfEvent);
        if (!chartInstance->c1_dataWrittenToVector[11U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(12U, 4U, 7U,
            chartInstance->c1_sfEvent, false);
        }

        if (!chartInstance->c1_dataWrittenToVector[24U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(6U, 4U, 7U,
            chartInstance->c1_sfEvent, false);
        }

        chartInstance->c1_waypoints_reached_l += chartInstance->c1_arrived;
        chartInstance->c1_dataWrittenToVector[11U] = true;
        _SFD_DATA_RANGE_CHECK(chartInstance->c1_waypoints_reached_l, 12U, 4U, 7U,
                              chartInstance->c1_sfEvent, false);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                     chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_j_debug_family_names,
          c1_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargin, 0U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargout, 1U,
          c1_sf_marshallOut, c1_sf_marshallIn);
        if (!chartInstance->c1_dataWrittenToVector[14U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(13U, 4U, 6U,
            chartInstance->c1_sfEvent, false);
        }

        if (!chartInstance->c1_dataWrittenToVector[12U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(14U, 4U, 6U,
            chartInstance->c1_sfEvent, false);
        }

        c1_hoistedGlobal = *chartInstance->c1_xpos;
        c1_b_hoistedGlobal = *chartInstance->c1_ypos;
        c1_c_hoistedGlobal = chartInstance->c1_xlocal;
        c1_d_hoistedGlobal = chartInstance->c1_ylocal;
        c1_currentx = c1_hoistedGlobal;
        c1_currenty = c1_b_hoistedGlobal;
        c1_xdest = c1_c_hoistedGlobal;
        c1_ydest = c1_d_hoistedGlobal;
        _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c1_k_debug_family_names,
          c1_d_debug_family_var_map);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                     chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_j_nargin, 0U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_j_nargout, 1U,
          c1_sf_marshallOut, c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_currentx, 2U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_currenty, 3U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_xdest, 4U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ydest, 5U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                     chartInstance->c1_sfEvent);
        c1_x = c1_xdest - c1_currentx;
        c1_b_x = c1_x;
        c1_c_x = c1_b_x;
        c1_y = muDoubleScalarAbs(c1_c_x);
        guard1 = false;
        if (CV_EML_COND(13, 0, 0, c1_y <= 0.01)) {
          c1_d_x = c1_ydest - c1_currenty;
          c1_e_x = c1_d_x;
          c1_f_x = c1_e_x;
          c1_d_y = muDoubleScalarAbs(c1_f_x);
          if (CV_EML_COND(13, 0, 1, c1_d_y <= 0.01)) {
            CV_EML_MCDC(13, 0, 0, true);
            CV_EML_IF(13, 0, 0, true);
            c1_b_sf_internal_predicateOutput = true;
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          CV_EML_MCDC(13, 0, 0, false);
          CV_EML_IF(13, 0, 0, false);
          c1_b_sf_internal_predicateOutput = false;
        }

        if (c1_b_sf_internal_predicateOutput) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
          chartInstance->c1_arrived = 1.0;
          chartInstance->c1_dataWrittenToVector[24U] = true;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_arrived, 6U, 5U, 4U,
                                chartInstance->c1_sfEvent, false);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
          chartInstance->c1_arrived = 0.0;
          chartInstance->c1_dataWrittenToVector[24U] = true;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_arrived, 6U, 5U, 15U,
                                chartInstance->c1_sfEvent, false);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_POP();
        _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_POP();
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_S4_checkifdone:
      CV_CHART_EVAL(0, 0, 5);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                   chartInstance->c1_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c1_p_debug_family_names,
        c1_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargin, 0U, c1_sf_marshallOut,
        c1_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargout, 1U, c1_sf_marshallOut,
        c1_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_out, 2U, c1_b_sf_marshallOut,
        c1_b_sf_marshallIn);
      if (!chartInstance->c1_dataWrittenToVector[4U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(7U, 5U, 19U, chartInstance->c1_sfEvent,
          false);
      }

      c1_c_out = CV_EML_IF(19, 0, 0, CV_RELATIONAL_EVAL(5U, 19U, 0,
        chartInstance->c1_finished, 0.0, -1, 0U, chartInstance->c1_finished ==
        0.0));
      _SFD_SYMBOL_SCOPE_POP();
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_S4_checkifdone = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_kwane_crane = c1_IN_S1_Initialize;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_S1_Initialize = 1U;
        c1_enter_internal_S1_Initialize(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 20U,
                     chartInstance->c1_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c1_r_debug_family_names,
          c1_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_f_nargin, 0U, c1_sf_marshallOut,
          c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_f_nargout, 1U,
          c1_sf_marshallOut, c1_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_out, 2U, c1_b_sf_marshallOut,
          c1_b_sf_marshallIn);
        if (!chartInstance->c1_dataWrittenToVector[4U]) {
          _SFD_DATA_READ_BEFORE_WRITE_ERROR(7U, 5U, 20U,
            chartInstance->c1_sfEvent, false);
        }

        c1_d_out = CV_EML_IF(20, 0, 0, CV_RELATIONAL_EVAL(5U, 20U, 0,
          chartInstance->c1_finished, 1.0, -1, 0U, chartInstance->c1_finished ==
          1.0));
        _SFD_SYMBOL_SCOPE_POP();
        if (c1_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_S4_checkifdone = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_c1_kwane_crane = c1_IN_S5_done;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_S5_done = 1U;
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_n_debug_family_names,
            c1_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_h_nargin, 0U,
            c1_sf_marshallOut, c1_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_h_nargout, 1U,
            c1_sf_marshallOut, c1_sf_marshallIn);
          *chartInstance->c1_done = true;
          chartInstance->c1_dataWrittenToVector[0U] = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_done, 21U, 4U, 8U,
                                chartInstance->c1_sfEvent, false);
          if (!chartInstance->c1_dataWrittenToVector[11U]) {
            _SFD_DATA_READ_BEFORE_WRITE_ERROR(12U, 4U, 8U,
              chartInstance->c1_sfEvent, false);
          }

          *chartInstance->c1_waypoints_reached =
            chartInstance->c1_waypoints_reached_l;
          chartInstance->c1_dataWrittenToVector[10U] = true;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_waypoints_reached, 30U, 4U,
                                8U, chartInstance->c1_sfEvent, false);
          if (!chartInstance->c1_dataWrittenToVector[10U]) {
            _SFD_DATA_READ_BEFORE_WRITE_ERROR(30U, 4U, 8U,
              chartInstance->c1_sfEvent, false);
          }

          sf_mex_printf("%s =\\n", "waypoints_reached");
          c1_g_hoistedGlobal = *chartInstance->c1_waypoints_reached;
          c1_b_y = NULL;
          sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_g_hoistedGlobal, 0, 0U,
            0U, 0U, 0), false);
          sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14,
                            c1_b_y);
          _SFD_SYMBOL_SCOPE_POP();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                       chartInstance->c1_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_S5_done:
      CV_CHART_EVAL(0, 0, 6);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c1_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c1_is_c1_kwane_crane = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_kwane_crane(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_enter_internal_S1_Initialize(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  uint32_T c1_debug_family_var_map[2];
  real_T c1_nargin = 0.0;
  real_T c1_nargout = 0.0;
  real_T c1_b_nargin = 0.0;
  real_T c1_b_nargout = 0.0;
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_ycurrent;
  real_T c1_ydest;
  uint32_T c1_b_debug_family_var_map[4];
  real_T c1_c_nargin = 2.0;
  real_T c1_c_nargout = 0.0;
  real_T c1_d0;
  real_T c1_d1;
  real_T c1_d2;
  real_T c1_d3;
  real_T c1_d4;
  real_T c1_d5;
  real_T c1_d6;
  real_T c1_d7;
  real_T c1_c_hoistedGlobal;
  const mxArray *c1_y = NULL;
  real_T c1_d_hoistedGlobal;
  const mxArray *c1_b_y = NULL;
  real_T c1_e_hoistedGlobal;
  const mxArray *c1_c_y = NULL;
  real_T c1_f_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_nargin = 0.0;
  real_T c1_d_nargout = 0.0;
  real_T c1_g_hoistedGlobal;
  real_T c1_h_hoistedGlobal;
  real_T c1_xcurrent;
  real_T c1_xdest;
  real_T c1_e_nargin = 2.0;
  real_T c1_e_nargout = 0.0;
  real_T c1_d8;
  real_T c1_d9;
  real_T c1_d10;
  real_T c1_d11;
  real_T c1_d12;
  real_T c1_d13;
  real_T c1_d14;
  real_T c1_d15;
  real_T c1_i_hoistedGlobal;
  const mxArray *c1_e_y = NULL;
  real_T c1_j_hoistedGlobal;
  const mxArray *c1_f_y = NULL;
  real_T c1_k_hoistedGlobal;
  const mxArray *c1_g_y = NULL;
  real_T c1_l_hoistedGlobal;
  const mxArray *c1_h_y = NULL;
  chartInstance->c1_is_active_S1_setpoints1 = 1U;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_setpoints1 = 1U;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_b_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  if (!chartInstance->c1_dataWrittenToVector[13U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U, 4U, 2U, chartInstance->c1_sfEvent,
      false);
  }

  chartInstance->c1_xlocal = (*chartInstance->c1_xwaypoints)
    [sf_array_bounds_check(sfGlobalDebugInstanceStruct, chartInstance->S, 12U,
    21, 24, 16U, sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
    chartInstance->S, 12U, 28, 17, 16U, (int32_T)sf_integer_check
    (chartInstance->S, 12U, 28U, 17U, chartInstance->c1_index), 1, 7) - 1, 0, 6)];
  chartInstance->c1_dataWrittenToVector[14U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_xlocal, 13U, 4U, 2U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[13U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U, 4U, 2U, chartInstance->c1_sfEvent,
      false);
  }

  chartInstance->c1_ylocal = (*chartInstance->c1_ywaypoints)
    [sf_array_bounds_check(sfGlobalDebugInstanceStruct, chartInstance->S, 12U,
    47, 24, 17U, sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
    chartInstance->S, 12U, 54, 17, 17U, (int32_T)sf_integer_check
    (chartInstance->S, 12U, 54U, 17U, chartInstance->c1_index), 1, 7) - 1, 0, 6)];
  chartInstance->c1_dataWrittenToVector[12U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_ylocal, 14U, 4U, 2U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_arrived = 0.0;
  chartInstance->c1_dataWrittenToVector[24U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_arrived, 6U, 4U, 2U,
                        chartInstance->c1_sfEvent, false);
  _SFD_SYMBOL_SCOPE_POP();
  chartInstance->c1_is_active_S1_setup_pidy1 = 1U;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_setup_pidy1 = 1U;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_c_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  if (!chartInstance->c1_dataWrittenToVector[13U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U, 4U, 4U, chartInstance->c1_sfEvent,
      false);
  }

  c1_hoistedGlobal = *chartInstance->c1_ypos;
  c1_b_hoistedGlobal = chartInstance->c1_index;
  c1_ycurrent = c1_hoistedGlobal;
  c1_ydest = (*chartInstance->c1_ywaypoints)[sf_array_bounds_check
    (sfGlobalDebugInstanceStruct, chartInstance->S, 11U, 41, 17, 17U,
     sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct, chartInstance->S,
      11U, 41, 17, 17U, (int32_T)sf_integer_check(chartInstance->S, 11U, 41U,
       17U, c1_b_hoistedGlobal), 1, 7) - 1, 0, 6)];
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_e_debug_family_names,
    c1_b_debug_family_var_map);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_c_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ycurrent, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ydest, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  c1_setpidy(chartInstance, c1_ycurrent, c1_ydest, &c1_d0, &c1_d1, &c1_d2,
             &c1_d3);
  c1_d4 = c1_d0;
  c1_d5 = c1_d1;
  c1_d6 = c1_d2;
  c1_d7 = c1_d3;
  chartInstance->c1_Ki_l = c1_d4;
  chartInstance->c1_dataWrittenToVector[20U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Ki_l, 0U, 5U, 3U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_Kpa_l = c1_d5;
  chartInstance->c1_dataWrittenToVector[15U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kpa_l, 3U, 5U, 3U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_Kp_l = c1_d6;
  chartInstance->c1_dataWrittenToVector[22U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kp_l, 2U, 5U, 3U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_tsy_l = c1_d7;
  chartInstance->c1_dataWrittenToVector[16U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_tsy_l, 11U, 5U, 3U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[20U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 5U, 3U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "Ki_l");
  c1_c_hoistedGlobal = chartInstance->c1_Ki_l;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_c_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_y);
  if (!chartInstance->c1_dataWrittenToVector[15U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(3U, 5U, 3U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "Kpa_l");
  c1_d_hoistedGlobal = chartInstance->c1_Kpa_l;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_d_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_b_y);
  if (!chartInstance->c1_dataWrittenToVector[22U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(2U, 5U, 3U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "Kp_l");
  c1_e_hoistedGlobal = chartInstance->c1_Kp_l;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_e_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_c_y);
  if (!chartInstance->c1_dataWrittenToVector[16U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(11U, 5U, 3U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "tsy_l");
  c1_f_hoistedGlobal = chartInstance->c1_tsy_l;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_f_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_d_y);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  chartInstance->c1_is_active_S1_setup_pidy = 1U;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_setup_pidy = 1U;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_f_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  if (!chartInstance->c1_dataWrittenToVector[13U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U, 4U, 3U, chartInstance->c1_sfEvent,
      false);
  }

  c1_g_hoistedGlobal = *chartInstance->c1_xpos;
  c1_h_hoistedGlobal = chartInstance->c1_index;
  c1_xcurrent = c1_g_hoistedGlobal;
  c1_xdest = (*chartInstance->c1_xwaypoints)[sf_array_bounds_check
    (sfGlobalDebugInstanceStruct, chartInstance->S, 13U, 42, 17, 16U,
     sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct, chartInstance->S,
      13U, 42, 17, 16U, (int32_T)sf_integer_check(chartInstance->S, 13U, 42U,
       17U, c1_h_hoistedGlobal), 1, 7) - 1, 0, 6)];
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c1_h_debug_family_names,
    c1_b_debug_family_var_map);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_e_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_xcurrent, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_xdest, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  c1_setpidx(chartInstance, c1_xcurrent, c1_xdest, &c1_d8, &c1_d9, &c1_d10,
             &c1_d11);
  c1_d12 = c1_d8;
  c1_d13 = c1_d9;
  c1_d14 = c1_d10;
  c1_d15 = c1_d11;
  chartInstance->c1_Kix_l = c1_d12;
  chartInstance->c1_dataWrittenToVector[17U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kix_l, 1U, 5U, 2U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_Kpax_l = c1_d13;
  chartInstance->c1_dataWrittenToVector[21U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kpax_l, 4U, 5U, 2U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_Kpx_l = c1_d14;
  chartInstance->c1_dataWrittenToVector[19U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Kpx_l, 5U, 5U, 2U,
                        chartInstance->c1_sfEvent, false);
  chartInstance->c1_tsx_l = c1_d15;
  chartInstance->c1_dataWrittenToVector[23U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_tsx_l, 10U, 5U, 2U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[17U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(1U, 5U, 2U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "Kix_l");
  c1_i_hoistedGlobal = chartInstance->c1_Kix_l;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_i_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_e_y);
  if (!chartInstance->c1_dataWrittenToVector[21U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(4U, 5U, 2U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "Kpax_l");
  c1_j_hoistedGlobal = chartInstance->c1_Kpax_l;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_j_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_f_y);
  if (!chartInstance->c1_dataWrittenToVector[19U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(5U, 5U, 2U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "Kpx_l");
  c1_k_hoistedGlobal = chartInstance->c1_Kpx_l;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_k_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_g_y);
  if (!chartInstance->c1_dataWrittenToVector[23U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U, 5U, 2U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "tsx_l");
  c1_l_hoistedGlobal = chartInstance->c1_tsx_l;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_l_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_h_y);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c1_S1_Initialize(SFc1_kwane_craneInstanceStruct *chartInstance)
{
  uint32_T c1_debug_family_var_map[2];
  real_T c1_nargin = 0.0;
  real_T c1_nargout = 0.0;
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  real_T c1_varargin_1;
  real_T c1_varargin_2;
  real_T c1_b_varargin_2;
  real_T c1_varargin_3;
  real_T c1_x;
  real_T c1_y;
  real_T c1_b_x;
  real_T c1_b_y;
  real_T c1_c_x;
  real_T c1_c_y;
  real_T c1_c_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_setup_pidy = 0U;
  chartInstance->c1_is_active_S1_setup_pidy = 0U;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_setup_pidy1 = 0U;
  chartInstance->c1_is_active_S1_setup_pidy1 = 0U;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_setpoints1 = 0U;
  chartInstance->c1_is_active_S1_setpoints1 = 0U;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S1_Initialize = 0U;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  chartInstance->c1_is_c1_kwane_crane = c1_IN_S2_Move_to_waypoint;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_S2_Move_to_waypoint = 1U;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c1_i_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  if (!chartInstance->c1_dataWrittenToVector[14U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(13U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_xref = chartInstance->c1_xlocal;
  chartInstance->c1_dataWrittenToVector[2U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_xref, 23U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[12U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(14U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_yref = chartInstance->c1_ylocal;
  chartInstance->c1_dataWrittenToVector[6U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_yref, 26U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[22U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(2U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_Kpy = chartInstance->c1_Kp_l;
  chartInstance->c1_dataWrittenToVector[7U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Kpy, 27U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[20U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_Kiy = chartInstance->c1_Ki_l;
  chartInstance->c1_dataWrittenToVector[8U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Kiy, 28U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[15U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(3U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_Kpay = chartInstance->c1_Kpa_l;
  chartInstance->c1_dataWrittenToVector[9U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Kpay, 29U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[17U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(1U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_kix = chartInstance->c1_Kix_l;
  chartInstance->c1_dataWrittenToVector[5U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_kix, 25U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[19U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(5U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_kpx = chartInstance->c1_Kpx_l;
  chartInstance->c1_dataWrittenToVector[3U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_kpx, 24U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[21U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(4U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  *chartInstance->c1_kpax = chartInstance->c1_Kpax_l;
  chartInstance->c1_dataWrittenToVector[1U] = true;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_kpax, 22U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[16U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(11U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  if (!chartInstance->c1_dataWrittenToVector[23U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  c1_hoistedGlobal = chartInstance->c1_tsy_l;
  c1_b_hoistedGlobal = chartInstance->c1_tsx_l;
  c1_varargin_1 = c1_hoistedGlobal;
  c1_varargin_2 = c1_b_hoistedGlobal;
  c1_b_varargin_2 = c1_varargin_1;
  c1_varargin_3 = c1_varargin_2;
  c1_x = c1_b_varargin_2;
  c1_y = c1_varargin_3;
  c1_b_x = c1_x;
  c1_b_y = c1_y;
  c1_c_x = c1_b_x;
  c1_c_y = c1_b_y;
  chartInstance->c1_ts = muDoubleScalarMax(c1_c_x, c1_c_y);
  chartInstance->c1_dataWrittenToVector[18U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_ts, 9U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  if (!chartInstance->c1_dataWrittenToVector[18U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(9U, 4U, 5U, chartInstance->c1_sfEvent,
      false);
  }

  sf_mex_printf("%s =\\n", "ts");
  c1_c_hoistedGlobal = chartInstance->c1_ts;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_d_y);
  chartInstance->c1_arrived = 0.0;
  chartInstance->c1_dataWrittenToVector[24U] = true;
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_arrived, 6U, 4U, 5U,
                        chartInstance->c1_sfEvent, false);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  (void)c1_chartNumber;
  (void)c1_instanceNumber;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct *chartInstance,
  const mxArray *c1_nargout, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d16;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d16, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d16;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  boolean_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(boolean_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static boolean_T c1_c_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_sf_internal_predicateOutput, const char_T
  *c1_identifier)
{
  boolean_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_sf_internal_predicateOutput), &c1_thisId);
  sf_mex_destroy(&c1_sf_internal_predicateOutput);
  return c1_y;
}

static boolean_T c1_d_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  boolean_T c1_y;
  boolean_T c1_b0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_b0, 1, 11, 0U, 0, 0U, 0);
  c1_y = c1_b0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_sf_internal_predicateOutput;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  boolean_T c1_y;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_sf_internal_predicateOutput = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_sf_internal_predicateOutput), &c1_thisId);
  sf_mex_destroy(&c1_sf_internal_predicateOutput);
  *(boolean_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_kwane_crane_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static void c1_setpidy(SFc1_kwane_craneInstanceStruct *chartInstance, real_T
  c1_ycurrent, real_T c1_ydest, real_T *c1_Ki, real_T *c1_Kpa, real_T *c1_Kp,
  real_T *c1_tsy)
{
  uint32_T c1_debug_family_var_map[10];
  real_T c1_temp0;
  real_T c1_temp;
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 4.0;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_y;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c1_d_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_temp0, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_temp, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ycurrent, 4U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_ydest, 5U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Ki, 6U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Kpa, 7U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Kp, 8U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_tsy, 9U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(14, 0);
  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 2);
  c1_x = c1_ycurrent - c1_ydest;
  c1_b_x = c1_x;
  c1_c_x = c1_b_x;
  c1_y = muDoubleScalarAbs(c1_c_x);
  c1_temp0 = c1_y * 100.0;
  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 3);
  c1_d_x = c1_temp0;
  c1_temp = c1_d_x;
  c1_e_x = c1_temp;
  c1_temp = c1_e_x;
  c1_f_x = c1_temp;
  c1_temp = c1_f_x;
  c1_temp = muDoubleScalarRound(c1_temp);
  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 4);
  if (CV_EML_IF(14, 1, 0, CV_RELATIONAL_EVAL(4U, 14U, 0, c1_temp, 0.0, -1, 0U,
        c1_temp == 0.0))) {
    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 5);
    *c1_Ki = 0.0;
    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 6);
    *c1_Kpa = 0.0;
    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 7);
    *c1_Kp = 0.0;
    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 8);
    *c1_tsy = 0.0;
  } else {
    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 9);
    if (CV_EML_IF(14, 1, 1, CV_RELATIONAL_EVAL(4U, 14U, 1, c1_temp, 1.0, -1, 0U,
          c1_temp == 1.0))) {
      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 10);
      *c1_Ki = 0.0;
      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 11);
      *c1_Kpa = 21.4621;
      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 12);
      *c1_Kp = 23.7;
      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 13);
      *c1_tsy = 3.0;
    } else {
      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 14);
      if (CV_EML_IF(14, 1, 2, CV_RELATIONAL_EVAL(4U, 14U, 2, c1_temp, 2.0, -1,
            0U, c1_temp == 2.0))) {
        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 15);
        *c1_Ki = 0.0;
        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 16);
        *c1_Kpa = 18.7134;
        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 17);
        *c1_Kp = 12.8789;
        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 18);
        *c1_tsy = 3.0;
      } else {
        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 19);
        if (CV_EML_IF(14, 1, 3, CV_RELATIONAL_EVAL(4U, 14U, 3, c1_temp, 3.0, -1,
              0U, c1_temp == 3.0))) {
          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 20);
          *c1_Ki = 0.0;
          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 21);
          *c1_Kpa = 19.2515;
          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 22);
          *c1_Kp = 8.8615;
          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 23);
          *c1_tsy = 3.0;
        } else {
          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 24);
          if (CV_EML_IF(14, 1, 4, CV_RELATIONAL_EVAL(4U, 14U, 4, c1_temp, 4.0,
                -1, 0U, c1_temp == 4.0))) {
            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 25);
            *c1_Ki = 0.0;
            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 26);
            *c1_Kpa = 19.815;
            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 27);
            *c1_Kp = 7.0;
            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 28);
            *c1_tsy = 3.0;
          } else {
            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 29);
            if (CV_EML_IF(14, 1, 5, CV_RELATIONAL_EVAL(4U, 14U, 5, c1_temp, 7.0,
                  -1, 3U, c1_temp <= 7.0))) {
              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 30);
              *c1_Ki = 0.0;
              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 31);
              *c1_Kpa = 30.0;
              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 32);
              *c1_Kp = 4.921;
              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 33);
              *c1_tsy = 4.5;
            } else {
              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 34);
              if (CV_EML_IF(14, 1, 6, CV_RELATIONAL_EVAL(4U, 14U, 6, c1_temp,
                    10.0, -1, 3U, c1_temp <= 10.0))) {
                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 35);
                *c1_Ki = 0.0789;
                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 36);
                *c1_Kpa = 22.9519;
                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 37);
                *c1_Kp = 3.6548;
                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 38);
                *c1_tsy = 4.5;
              } else {
                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 39);
                if (CV_EML_IF(14, 1, 7, CV_RELATIONAL_EVAL(4U, 14U, 7, c1_temp,
                      15.0, -1, 3U, c1_temp <= 15.0))) {
                  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 40);
                  *c1_Ki = 0.0694;
                  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 41);
                  *c1_Kpa = 19.6705;
                  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 42);
                  *c1_Kp = 3.005;
                  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 43);
                  *c1_tsy = 5.5;
                } else {
                  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 44);
                  if (CV_EML_IF(14, 1, 8, CV_RELATIONAL_EVAL(4U, 14U, 8, c1_temp,
                        20.0, -1, 3U, c1_temp <= 20.0))) {
                    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 45);
                    *c1_Ki = 0.0723;
                    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 46);
                    *c1_Kpa = 19.8372;
                    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 47);
                    *c1_Kp = 2.2143;
                    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 48);
                    *c1_tsy = 5.5;
                  } else {
                    _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 49);
                    if (CV_EML_IF(14, 1, 9, CV_RELATIONAL_EVAL(4U, 14U, 9,
                          c1_temp, 25.0, -1, 3U, c1_temp <= 25.0))) {
                      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 50);
                      *c1_Ki = 0.031;
                      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 51);
                      *c1_Kpa = 22.8874;
                      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 52);
                      *c1_Kp = 1.9582;
                      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 53);
                      *c1_tsy = 5.5;
                    } else {
                      _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 54);
                      if (CV_EML_IF(14, 1, 10, CV_RELATIONAL_EVAL(4U, 14U, 10,
                            c1_temp, 30.0, -1, 3U, c1_temp <= 30.0))) {
                        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 55);
                        *c1_Ki = 0.1018;
                        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 56);
                        *c1_Kpa = 16.9781;
                        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 57);
                        *c1_Kp = 1.538;
                        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 58);
                        *c1_tsy = 5.5;
                      } else {
                        _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 59);
                        if (CV_EML_IF(14, 1, 11, CV_RELATIONAL_EVAL(4U, 14U, 11,
                              c1_temp, 35.0, -1, 3U, c1_temp <= 35.0))) {
                          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 60);
                          *c1_Ki = 0.1017;
                          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 61);
                          *c1_Kpa = 15.6134;
                          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 62);
                          *c1_Kp = 1.3479;
                          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 63);
                          *c1_tsy = 6.0;
                        } else {
                          _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 64);
                          if (CV_EML_IF(14, 1, 12, CV_RELATIONAL_EVAL(4U, 14U,
                                12, c1_temp, 40.0, -1, 3U, c1_temp <= 40.0))) {
                            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 65);
                            *c1_Ki = 0.097;
                            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 66);
                            *c1_Kpa = 13.6476;
                            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 67);
                            *c1_Kp = 1.1919;
                            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 68);
                            *c1_tsy = 6.0;
                          } else {
                            _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 69);
                            if (CV_EML_IF(14, 1, 13, CV_RELATIONAL_EVAL(4U, 14U,
                                  13, c1_temp, 45.0, -1, 3U, c1_temp <= 45.0)))
                            {
                              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 70);
                              *c1_Ki = 0.0553;
                              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 71);
                              *c1_Kpa = 20.0;
                              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 72);
                              *c1_Kp = 1.2126;
                              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 73);
                              *c1_tsy = 6.0;
                            } else {
                              _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 74);
                              if (CV_EML_IF(14, 1, 14, CV_RELATIONAL_EVAL(4U,
                                    14U, 14, c1_temp, 47.0, -1, 3U, c1_temp <=
                                    47.0))) {
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 75);
                                *c1_Ki = 0.0526;
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 76);
                                *c1_Kpa = 19.8667;
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 77);
                                *c1_Kp = 1.1418;
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 78);
                                *c1_tsy = 6.0;
                              } else {
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 80);
                                *c1_Ki = 0.0;
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 81);
                                *c1_Kpa = 0.0;
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 82);
                                *c1_Kp = 0.0;
                                _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, 83);
                                *c1_tsy = 0.0;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  _SFD_EML_CALL(14U, chartInstance->c1_sfEvent, -83);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c1_setpidx(SFc1_kwane_craneInstanceStruct *chartInstance, real_T
  c1_xcurrent, real_T c1_xdest, real_T *c1_Kix, real_T *c1_Kpax, real_T *c1_Kpx,
  real_T *c1_tsx)
{
  uint32_T c1_debug_family_var_map[10];
  real_T c1_temp0;
  real_T c1_temp;
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 4.0;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_y;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_f_x;
  const mxArray *c1_b_y = NULL;
  const mxArray *c1_c_y = NULL;
  const mxArray *c1_d_y = NULL;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c1_g_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_temp0, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_temp, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 2U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_xcurrent, 4U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_xdest, 5U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Kix, 6U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Kpax, 7U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Kpx, 8U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_tsx, 9U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(13, 0);
  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 2);
  c1_x = c1_xcurrent - c1_xdest;
  c1_b_x = c1_x;
  c1_c_x = c1_b_x;
  c1_y = muDoubleScalarAbs(c1_c_x);
  c1_temp0 = c1_y * 100.0;
  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 3);
  c1_d_x = c1_temp0;
  c1_temp = c1_d_x;
  c1_e_x = c1_temp;
  c1_temp = c1_e_x;
  c1_f_x = c1_temp;
  c1_temp = c1_f_x;
  c1_temp = muDoubleScalarRound(c1_temp);
  sf_mex_printf("%s =\\n", "temp");
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_temp, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c1_b_y);
  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 4);
  if (CV_EML_IF(13, 1, 0, CV_RELATIONAL_EVAL(4U, 13U, 0, c1_temp, 0.0, -1, 0U,
        c1_temp == 0.0))) {
    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 5);
    *c1_Kix = 0.0;
    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 6);
    *c1_Kpax = 0.0;
    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 7);
    *c1_Kpx = 0.0;
    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 8);
    *c1_tsx = 0.0;
  } else {
    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 9);
    if (CV_EML_IF(13, 1, 1, CV_RELATIONAL_EVAL(4U, 13U, 1, c1_temp, 1.0, -1, 0U,
          c1_temp == 1.0))) {
      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 10);
      *c1_Kix = 0.0;
      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 11);
      *c1_Kpax = 35.913;
      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 12);
      *c1_Kpx = 29.9661;
      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 13);
      *c1_tsx = 3.0;
    } else {
      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 14);
      if (CV_EML_IF(13, 1, 2, CV_RELATIONAL_EVAL(4U, 13U, 2, c1_temp, 2.0, -1,
            0U, c1_temp == 2.0))) {
        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 15);
        *c1_Kix = 0.0;
        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 16);
        *c1_Kpax = 31.4919;
        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 17);
        *c1_Kpx = 16.0003;
        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 18);
        *c1_tsx = 3.0;
      } else {
        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 19);
        if (CV_EML_IF(13, 1, 3, CV_RELATIONAL_EVAL(4U, 13U, 3, c1_temp, 3.0, -1,
              0U, c1_temp == 3.0))) {
          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 20);
          *c1_Kix = 0.0;
          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 21);
          *c1_Kpax = 28.7753;
          sf_mex_printf("%s =\\n", "Kpax");
          c1_c_y = NULL;
          sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_Kpax, 0, 0U, 0U, 0U, 0),
                        false);
          sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14,
                            c1_c_y);
          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 22);
          *c1_Kpx = 10.9142;
          sf_mex_printf("%s =\\n", "Kpx");
          c1_d_y = NULL;
          sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_Kpx, 0, 0U, 0U, 0U, 0),
                        false);
          sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14,
                            c1_d_y);
          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 23);
          *c1_tsx = 3.0;
        } else {
          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 24);
          if (CV_EML_IF(13, 1, 4, CV_RELATIONAL_EVAL(4U, 13U, 4, c1_temp, 4.0,
                -1, 0U, c1_temp == 4.0))) {
            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 25);
            *c1_Kix = 0.0;
            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 26);
            *c1_Kpax = 27.0726;
            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 27);
            *c1_Kpx = 8.2798;
            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 28);
            *c1_tsx = 3.0;
          } else {
            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 29);
            if (CV_EML_IF(13, 1, 5, CV_RELATIONAL_EVAL(4U, 13U, 5, c1_temp, 7.0,
                  -1, 3U, c1_temp <= 7.0))) {
              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 30);
              *c1_Kix = 0.0;
              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 31);
              *c1_Kpax = 28.8807;
              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 32);
              *c1_Kpx = 6.8;
              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 33);
              *c1_tsx = 4.5;
            } else {
              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 34);
              if (CV_EML_IF(13, 1, 6, CV_RELATIONAL_EVAL(4U, 13U, 6, c1_temp,
                    10.0, -1, 3U, c1_temp <= 10.0))) {
                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 35);
                *c1_Kix = -0.1337;
                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 36);
                *c1_Kpax = 29.9504;
                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 37);
                *c1_Kpx = 5.1631;
                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 38);
                *c1_tsx = 4.5;
              } else {
                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 39);
                if (CV_EML_IF(13, 1, 7, CV_RELATIONAL_EVAL(4U, 13U, 7, c1_temp,
                      15.0, -1, 3U, c1_temp <= 15.0))) {
                  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 40);
                  *c1_Kix = -0.1312;
                  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 41);
                  *c1_Kpax = 29.7874;
                  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 42);
                  *c1_Kpx = 3.8515;
                  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 43);
                  *c1_tsx = 5.5;
                } else {
                  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 44);
                  if (CV_EML_IF(13, 1, 8, CV_RELATIONAL_EVAL(4U, 13U, 8, c1_temp,
                        20.0, -1, 3U, c1_temp <= 20.0))) {
                    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 45);
                    *c1_Kix = -0.1315;
                    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 46);
                    *c1_Kpax = 29.7281;
                    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 47);
                    *c1_Kpx = 3.2651;
                    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 48);
                    *c1_tsx = 5.5;
                  } else {
                    _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 49);
                    if (CV_EML_IF(13, 1, 9, CV_RELATIONAL_EVAL(4U, 13U, 9,
                          c1_temp, 25.0, -1, 3U, c1_temp <= 25.0))) {
                      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 50);
                      *c1_Kix = -0.0549;
                      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 51);
                      *c1_Kpax = 35.0;
                      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 52);
                      *c1_Kpx = 2.49;
                      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 53);
                      *c1_tsx = 5.5;
                    } else {
                      _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 54);
                      if (CV_EML_IF(13, 1, 10, CV_RELATIONAL_EVAL(4U, 13U, 10,
                            c1_temp, 30.0, -1, 3U, c1_temp <= 30.0))) {
                        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 55);
                        *c1_Kix = -0.0757;
                        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 56);
                        *c1_Kpax = 40.0;
                        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 57);
                        *c1_Kpx = 2.24;
                        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 58);
                        *c1_tsx = 5.5;
                      } else {
                        _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 59);
                        if (CV_EML_IF(13, 1, 11, CV_RELATIONAL_EVAL(4U, 13U, 11,
                              c1_temp, 35.0, -1, 3U, c1_temp <= 35.0))) {
                          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 60);
                          *c1_Kix = -0.0613;
                          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 61);
                          *c1_Kpax = 41.2866;
                          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 62);
                          *c1_Kpx = 2.0264;
                          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 63);
                          *c1_tsx = 6.0;
                        } else {
                          _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 64);
                          if (CV_EML_IF(13, 1, 12, CV_RELATIONAL_EVAL(4U, 13U,
                                12, c1_temp, 40.0, -1, 3U, c1_temp <= 40.0))) {
                            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 65);
                            *c1_Kix = -0.0536;
                            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 66);
                            *c1_Kpax = 42.2712;
                            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 67);
                            *c1_Kpx = 1.8435;
                            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 68);
                            *c1_tsx = 6.0;
                          } else {
                            _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 69);
                            if (CV_EML_IF(13, 1, 13, CV_RELATIONAL_EVAL(4U, 13U,
                                  13, c1_temp, 45.0, -1, 3U, c1_temp <= 45.0)))
                            {
                              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 70);
                              *c1_Kix = -0.0026;
                              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 71);
                              *c1_Kpax = 35.2599;
                              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 72);
                              *c1_Kpx = 1.5553;
                              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 73);
                              *c1_tsx = 6.0;
                            } else {
                              _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 74);
                              if (CV_EML_IF(13, 1, 14, CV_RELATIONAL_EVAL(4U,
                                    13U, 14, c1_temp, 47.0, -1, 3U, c1_temp <=
                                    47.0))) {
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 75);
                                *c1_Kix = -0.001;
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 76);
                                *c1_Kpax = 35.2696;
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 77);
                                *c1_Kpx = 1.4588;
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 78);
                                *c1_tsx = 6.0;
                              } else {
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 80);
                                *c1_Kix = 0.0;
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 81);
                                *c1_Kpax = 0.0;
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 82);
                                *c1_Kpx = 0.0;
                                _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, 83);
                                *c1_tsx = 0.0;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  _SFD_EML_CALL(13U, chartInstance->c1_sfEvent, -83);
  _SFD_SYMBOL_SCOPE_POP();
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i3;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i3, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i3;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  uint8_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint8_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_b_tp_S0_IDLE, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_tp_S0_IDLE),
    &c1_thisId);
  sf_mex_destroy(&c1_b_tp_S0_IDLE);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_tp_S0_IDLE;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y;
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_b_tp_S0_IDLE = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_tp_S0_IDLE),
    &c1_thisId);
  sf_mex_destroy(&c1_b_tp_S0_IDLE);
  *(uint8_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_i4;
  const mxArray *c1_y = NULL;
  real_T c1_u[7];
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  for (c1_i4 = 0; c1_i4 < 7; c1_i4++) {
    c1_u[c1_i4] = (*(real_T (*)[7])c1_inData)[c1_i4];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 7), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint32_T c1_h_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_b_temporalCounter_i1, const char_T
  *c1_identifier)
{
  uint32_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_temporalCounter_i1),
    &c1_thisId);
  sf_mex_destroy(&c1_b_temporalCounter_i1);
  return c1_y;
}

static uint32_T c1_i_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_y;
  uint32_T c1_u1;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u1, 1, 7, 0U, 0, 0U, 0);
  c1_y = c1_u1;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_j_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct *chartInstance,
  const mxArray *c1_b_dataWrittenToVector, const char_T *c1_identifier,
  boolean_T c1_y[33])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_dataWrittenToVector),
                        &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_dataWrittenToVector);
}

static void c1_k_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, boolean_T c1_y[33])
{
  boolean_T c1_bv1[33];
  int32_T c1_i5;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_bv1, 1, 11, 0U, 1, 0U, 1, 33);
  for (c1_i5 = 0; c1_i5 < 33; c1_i5++) {
    c1_y[c1_i5] = c1_bv1[c1_i5];
  }

  sf_mex_destroy(&c1_u);
}

static const mxArray *c1_l_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  sf_mex_assign(&c1_y, c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), false);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_m_emlrt_marshallIn(SFc1_kwane_craneInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  (void)chartInstance;
  (void)c1_parentId;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), false);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc1_kwane_craneInstanceStruct
  *chartInstance, int32_T c1_ssid)
{
  const mxArray *c1_msgInfo;
  (void)chartInstance;
  (void)c1_ssid;
  c1_msgInfo = NULL;
  return NULL;
}

static void c1_init_sf_message_store_memory(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_dsm_address_info(SFc1_kwane_craneInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_kwane_craneInstanceStruct
  *chartInstance)
{
  chartInstance->c1_xpos = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_done = (boolean_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_kpax = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_xref = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_kpx = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_xwaypoints = (real_T (*)[7])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_ywaypoints = (real_T (*)[7])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_start_course = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_total_waypoints = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_ypos = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_kix = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_yref = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_Kpy = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c1_Kiy = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c1_Kpay = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_waypoints_reached = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 10);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_kwane_crane_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4055704187U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1658592012U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(681765104U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3420629089U);
}

mxArray* sf_c1_kwane_crane_get_post_codegen_info(void);
mxArray *sf_c1_kwane_crane_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("qaWEbCadmLTi9vkuDh9Cz");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,10,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,15,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_kwane_crane_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_kwane_crane_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_kwane_crane_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_kwane_crane_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_kwane_crane_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c1_kwane_crane(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[103],T\"Kiy\",},{M[1],M[98],T\"Kpay\",},{M[1],M[105],T\"Kpy\",},{M[1],M[101],T\"done\",},{M[1],M[97],T\"kix\",},{M[1],M[100],T\"kpax\",},{M[1],M[99],T\"kpx\",},{M[1],M[96],T\"waypoints_reached\",},{M[1],M[102],T\"xref\",},{M[1],M[104],T\"yref\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[3],M[115],T\"Ki_l\",},{M[3],M[112],T\"Kix_l\",},{M[3],M[117],T\"Kp_l\",},{M[3],M[110],T\"Kpa_l\",},{M[3],M[116],T\"Kpax_l\",},{M[3],M[114],T\"Kpx_l\",},{M[3],M[119],T\"arrived\",},{M[3],M[89],T\"finished\",},{M[3],M[108],T\"index\",},{M[3],M[113],T\"ts\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[3],M[118],T\"tsx_l\",},{M[3],M[111],T\"tsy_l\",},{M[3],M[106],T\"waypoints_reached_l\",},{M[3],M[109],T\"xlocal\",},{M[3],M[107],T\"ylocal\",},{M[8],M[0],T\"is_active_c1_kwane_crane\",},{M[8],M[11],T\"is_active_S1_setup_pidy1\",},{M[8],M[12],T\"is_active_S1_setpoints1\",},{M[8],M[13],T\"is_active_S1_setup_pidy\",},{M[9],M[0],T\"is_c1_kwane_crane\",}}",
    "100 S1x2'type','srcId','name','auxInfo'{{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M[80],M[1]}}},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 32, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_kwane_crane_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc1_kwane_craneInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_kwane_craneInstanceStruct *chartInstance =
      (SFc1_kwane_craneInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _kwane_craneMachineNumber_,
           1,
           15,
           21,
           0,
           53,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_kwane_craneMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_kwane_craneMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _kwane_craneMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"Ki_l");
          _SFD_SET_DATA_PROPS(1,0,0,0,"Kix_l");
          _SFD_SET_DATA_PROPS(2,0,0,0,"Kp_l");
          _SFD_SET_DATA_PROPS(3,0,0,0,"Kpa_l");
          _SFD_SET_DATA_PROPS(4,0,0,0,"Kpax_l");
          _SFD_SET_DATA_PROPS(5,0,0,0,"Kpx_l");
          _SFD_SET_DATA_PROPS(6,0,0,0,"arrived");
          _SFD_SET_DATA_PROPS(7,0,0,0,"finished");
          _SFD_SET_DATA_PROPS(8,0,0,0,"index");
          _SFD_SET_DATA_PROPS(9,0,0,0,"ts");
          _SFD_SET_DATA_PROPS(10,0,0,0,"tsx_l");
          _SFD_SET_DATA_PROPS(11,0,0,0,"tsy_l");
          _SFD_SET_DATA_PROPS(12,0,0,0,"waypoints_reached_l");
          _SFD_SET_DATA_PROPS(13,0,0,0,"xlocal");
          _SFD_SET_DATA_PROPS(14,0,0,0,"ylocal");
          _SFD_SET_DATA_PROPS(15,1,1,0,"xpos");
          _SFD_SET_DATA_PROPS(16,1,1,0,"xwaypoints");
          _SFD_SET_DATA_PROPS(17,1,1,0,"ywaypoints");
          _SFD_SET_DATA_PROPS(18,1,1,0,"start_course");
          _SFD_SET_DATA_PROPS(19,1,1,0,"total_waypoints");
          _SFD_SET_DATA_PROPS(20,1,1,0,"ypos");
          _SFD_SET_DATA_PROPS(21,2,0,1,"done");
          _SFD_SET_DATA_PROPS(22,2,0,1,"kpax");
          _SFD_SET_DATA_PROPS(23,2,0,1,"xref");
          _SFD_SET_DATA_PROPS(24,2,0,1,"kpx");
          _SFD_SET_DATA_PROPS(25,2,0,1,"kix");
          _SFD_SET_DATA_PROPS(26,2,0,1,"yref");
          _SFD_SET_DATA_PROPS(27,2,0,1,"Kpy");
          _SFD_SET_DATA_PROPS(28,2,0,1,"Kiy");
          _SFD_SET_DATA_PROPS(29,2,0,1,"Kpay");
          _SFD_SET_DATA_PROPS(30,2,0,1,"waypoints_reached");
          _SFD_SET_DATA_PROPS(31,8,0,0,"");
          _SFD_SET_DATA_PROPS(32,8,0,0,"");
          _SFD_SET_DATA_PROPS(33,8,0,0,"");
          _SFD_SET_DATA_PROPS(34,8,0,0,"");
          _SFD_SET_DATA_PROPS(35,8,0,0,"");
          _SFD_SET_DATA_PROPS(36,8,0,0,"");
          _SFD_SET_DATA_PROPS(37,8,0,0,"");
          _SFD_SET_DATA_PROPS(38,8,0,0,"");
          _SFD_SET_DATA_PROPS(39,8,0,0,"");
          _SFD_SET_DATA_PROPS(40,8,0,0,"");
          _SFD_SET_DATA_PROPS(41,8,0,0,"");
          _SFD_SET_DATA_PROPS(42,8,0,0,"");
          _SFD_SET_DATA_PROPS(43,8,0,0,"");
          _SFD_SET_DATA_PROPS(44,8,0,0,"");
          _SFD_SET_DATA_PROPS(45,9,0,0,"");
          _SFD_SET_DATA_PROPS(46,9,0,0,"");
          _SFD_SET_DATA_PROPS(47,9,0,0,"");
          _SFD_SET_DATA_PROPS(48,9,0,0,"");
          _SFD_SET_DATA_PROPS(49,9,0,0,"");
          _SFD_SET_DATA_PROPS(50,9,0,0,"");
          _SFD_SET_DATA_PROPS(51,9,0,0,"");
          _SFD_SET_DATA_PROPS(52,9,0,0,"");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,1,0);
          _SFD_STATE_INFO(2,0,1);
          _SFD_STATE_INFO(3,0,1);
          _SFD_STATE_INFO(4,0,1);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,2);
          _SFD_STATE_INFO(10,0,2);
          _SFD_STATE_INFO(11,0,2);
          _SFD_STATE_INFO(12,0,2);
          _SFD_STATE_INFO(13,0,2);
          _SFD_STATE_INFO(14,0,2);
          _SFD_CH_SUBSTATE_COUNT(6);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,5);
          _SFD_CH_SUBSTATE_INDEX(3,6);
          _SFD_CH_SUBSTATE_INDEX(4,7);
          _SFD_CH_SUBSTATE_INDEX(5,8);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,3);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,4);
          _SFD_ST_SUBSTATE_INDEX(1,2,3);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
        }

        _SFD_CV_INIT_CHART(6,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,3,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(14,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(13,1,1,0,15,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(13,0,"setpidx",0,-1,1164);
        _SFD_CV_INIT_EML_IF(13,1,0,105,115,155,1164);
        _SFD_CV_INIT_EML_IF(13,1,1,155,169,221,1164);
        _SFD_CV_INIT_EML_IF(13,1,2,221,235,286,1164);
        _SFD_CV_INIT_EML_IF(13,1,3,286,300,348,1164);
        _SFD_CV_INIT_EML_IF(13,1,4,348,362,414,1164);
        _SFD_CV_INIT_EML_IF(13,1,5,414,429,478,1164);
        _SFD_CV_INIT_EML_IF(13,1,6,478,493,551,1164);
        _SFD_CV_INIT_EML_IF(13,1,7,551,566,624,1164);
        _SFD_CV_INIT_EML_IF(13,1,8,624,639,697,1164);
        _SFD_CV_INIT_EML_IF(13,1,9,697,712,764,1164);
        _SFD_CV_INIT_EML_IF(13,1,10,764,779,830,1164);
        _SFD_CV_INIT_EML_IF(13,1,11,830,845,902,1164);
        _SFD_CV_INIT_EML_IF(13,1,12,902,917,975,1164);
        _SFD_CV_INIT_EML_IF(13,1,13,975,990,1046,1164);
        _SFD_CV_INIT_EML_IF(13,1,14,1046,1061,1117,1164);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,0,108,115,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,1,162,169,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,2,228,235,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,3,293,300,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,4,355,362,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,5,421,429,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,6,485,493,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,7,558,566,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,8,631,639,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,9,704,712,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,10,771,779,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,11,837,845,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,12,909,917,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,13,982,990,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(13,1,14,1053,1061,-1,3);
        _SFD_CV_INIT_EML(14,1,1,0,15,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(14,0,"setpidy",0,-1,1102);
        _SFD_CV_INIT_EML_IF(14,1,0,103,113,151,1102);
        _SFD_CV_INIT_EML_IF(14,1,1,151,165,210,1102);
        _SFD_CV_INIT_EML_IF(14,1,2,210,224,272,1102);
        _SFD_CV_INIT_EML_IF(14,1,3,272,286,333,1102);
        _SFD_CV_INIT_EML_IF(14,1,4,333,347,389,1102);
        _SFD_CV_INIT_EML_IF(14,1,5,389,403,447,1102);
        _SFD_CV_INIT_EML_IF(14,1,6,447,462,516,1102);
        _SFD_CV_INIT_EML_IF(14,1,7,516,531,584,1102);
        _SFD_CV_INIT_EML_IF(14,1,8,584,599,654,1102);
        _SFD_CV_INIT_EML_IF(14,1,9,654,669,723,1102);
        _SFD_CV_INIT_EML_IF(14,1,10,723,738,791,1102);
        _SFD_CV_INIT_EML_IF(14,1,11,791,806,859,1102);
        _SFD_CV_INIT_EML_IF(14,1,12,859,874,927,1102);
        _SFD_CV_INIT_EML_IF(14,1,13,927,942,989,1102);
        _SFD_CV_INIT_EML_IF(14,1,14,989,1004,1058,1102);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,0,106,113,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,1,158,165,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,2,217,224,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,3,279,286,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,4,340,347,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,5,396,403,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,6,454,462,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,7,523,531,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,8,591,599,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,9,661,669,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,10,730,738,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,11,798,806,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,12,866,874,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,13,934,942,-1,3);
        _SFD_CV_INIT_EML_RELATIONAL(14,1,14,996,1004,-1,3);
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(3,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(6,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(7,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(8,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(3,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(12,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(13,0,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(13,0,0,1,53,1,48);

        {
          static int condStart[] = { 1, 28 };

          static int condEnd[] = { 26, 53 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(13,0,0,1,53,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML(15,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(6,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(7,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(14,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(8,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(8,0,0,1,12,1,12);
        _SFD_CV_INIT_EML(9,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(11,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(10,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,1,16,1,16);
        _SFD_CV_INIT_EML_RELATIONAL(1,0,0,1,16,-1,0);
        _SFD_CV_INIT_EML(19,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(19,0,0,1,12,1,12);
        _SFD_CV_INIT_EML_RELATIONAL(19,0,0,1,12,-1,0);
        _SFD_CV_INIT_EML(18,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(18,0,0,0,13,0,13);
        _SFD_CV_INIT_EML(20,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(20,0,0,1,12,1,12);
        _SFD_CV_INIT_EML_RELATIONAL(20,0,0,1,12,-1,0);
        _SFD_CV_INIT_EML(9,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(10,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(11,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(12,1,0,0,0,0,0,0,0,0,0,0);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 7U;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7U;
          _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(31,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(32,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(33,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(34,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(35,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(36,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(37,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(38,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(39,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(40,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(41,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(42,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(43,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(44,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(45,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(46,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(47,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(48,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(49,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(50,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(51,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(52,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_VALUE_PTR(31,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(32,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(33,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(34,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(35,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(36,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(37,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(38,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(39,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(40,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(41,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(42,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(43,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(44,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(45,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(46,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(47,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(48,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(49,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(50,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(51,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(52,(void *)(NULL));
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _kwane_craneMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_kwane_craneInstanceStruct *chartInstance =
      (SFc1_kwane_craneInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(15U, chartInstance->c1_xpos);
        _SFD_SET_DATA_VALUE_PTR(21U, chartInstance->c1_done);
        _SFD_SET_DATA_VALUE_PTR(22U, chartInstance->c1_kpax);
        _SFD_SET_DATA_VALUE_PTR(23U, chartInstance->c1_xref);
        _SFD_SET_DATA_VALUE_PTR(24U, chartInstance->c1_kpx);
        _SFD_SET_DATA_VALUE_PTR(7U, &chartInstance->c1_finished);
        _SFD_SET_DATA_VALUE_PTR(16U, *chartInstance->c1_xwaypoints);
        _SFD_SET_DATA_VALUE_PTR(17U, *chartInstance->c1_ywaypoints);
        _SFD_SET_DATA_VALUE_PTR(18U, chartInstance->c1_start_course);
        _SFD_SET_DATA_VALUE_PTR(19U, chartInstance->c1_total_waypoints);
        _SFD_SET_DATA_VALUE_PTR(20U, chartInstance->c1_ypos);
        _SFD_SET_DATA_VALUE_PTR(25U, chartInstance->c1_kix);
        _SFD_SET_DATA_VALUE_PTR(26U, chartInstance->c1_yref);
        _SFD_SET_DATA_VALUE_PTR(27U, chartInstance->c1_Kpy);
        _SFD_SET_DATA_VALUE_PTR(28U, chartInstance->c1_Kiy);
        _SFD_SET_DATA_VALUE_PTR(29U, chartInstance->c1_Kpay);
        _SFD_SET_DATA_VALUE_PTR(30U, chartInstance->c1_waypoints_reached);
        _SFD_SET_DATA_VALUE_PTR(12U, &chartInstance->c1_waypoints_reached_l);
        _SFD_SET_DATA_VALUE_PTR(14U, &chartInstance->c1_ylocal);
        _SFD_SET_DATA_VALUE_PTR(8U, &chartInstance->c1_index);
        _SFD_SET_DATA_VALUE_PTR(13U, &chartInstance->c1_xlocal);
        _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c1_Kpa_l);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c1_tsy_l);
        _SFD_SET_DATA_VALUE_PTR(1U, &chartInstance->c1_Kix_l);
        _SFD_SET_DATA_VALUE_PTR(9U, &chartInstance->c1_ts);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c1_Kpx_l);
        _SFD_SET_DATA_VALUE_PTR(0U, &chartInstance->c1_Ki_l);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c1_Kpax_l);
        _SFD_SET_DATA_VALUE_PTR(2U, &chartInstance->c1_Kp_l);
        _SFD_SET_DATA_VALUE_PTR(10U, &chartInstance->c1_tsx_l);
        _SFD_SET_DATA_VALUE_PTR(6U, &chartInstance->c1_arrived);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s5MEc2jZNwtf9yxXMXJZOIH";
}

static void sf_opaque_initialize_c1_kwane_crane(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_kwane_craneInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*)
    chartInstanceVar);
  initialize_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_kwane_crane(void *chartInstanceVar)
{
  enable_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_kwane_crane(void *chartInstanceVar)
{
  disable_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_kwane_crane(void *chartInstanceVar)
{
  sf_gateway_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_kwane_crane(SimStruct* S)
{
  return get_sim_state_c1_kwane_crane((SFc1_kwane_craneInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_kwane_crane(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c1_kwane_crane(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_kwane_craneInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_kwane_crane_optimization_info();
    }

    finalize_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_kwane_crane((SFc1_kwane_craneInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_kwane_crane(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_kwane_crane((SFc1_kwane_craneInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c1_kwane_crane(SimStruct *S)
{
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  ssSetModelReferenceSampleTimeDisallowInheritance(S);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_kwane_crane_optimization_info(sim_mode_is_rtw_gen
      (S), sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 1);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,6);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,10);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=10; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 6; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1849363064U));
  ssSetChecksum1(S,(1532887286U));
  ssSetChecksum2(S,(3804223000U));
  ssSetChecksum3(S,(697426948U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_kwane_crane(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_kwane_crane(SimStruct *S)
{
  SFc1_kwane_craneInstanceStruct *chartInstance;
  chartInstance = (SFc1_kwane_craneInstanceStruct *)utMalloc(sizeof
    (SFc1_kwane_craneInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_kwane_craneInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_kwane_crane;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_kwane_crane;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_kwane_crane;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_kwane_crane;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_kwane_crane;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_kwane_crane;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_kwane_crane;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_kwane_crane;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_kwane_crane;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_kwane_crane;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_kwane_crane;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c1_kwane_crane(chartInstance);
}

void c1_kwane_crane_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_kwane_crane(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_kwane_crane(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_kwane_crane(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_kwane_crane_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
