#pragma once
/**
   @section spatial-quantities-notation Spatial Quantities Notation

   This file contains documentation relating spatial quantities notation in this software to their identities
   found in: Mitiguy, P. "Advanced Dynamics and Motion Simulation", MotionGenesis, San Mateo, CA, USA, 2008.

   @note See https://drake.mit.edu/doxygen_cxx/group__multibody__notation.html for details on frame naming and
   notation.

   @paragraph offset-frames Offset Frame Notation

   The notation for frames that use an uppercase letter followed by a lowercase letter (e.g., Sa and Rb) express an
   "offset frame".  Offset frames are affixed to and aligned-with their capital letter body frame with origin
   translationally offset to a point denoted by the lower case letter.  For example, a frame with monogram notation `Sa`
   is aligned with Frame S and its origin is offset from the origin of Frame S, Point So, by `p_SoSa_S`. See
   https://drake.mit.edu/doxygen_cxx/group__multibody__frames__and__bodies.html for more information.

   @section rotational-quantities Rotational Quantities
   @subsection rotational-quantity-identities Rotational Quantity Identities

   The orientation of Frame S in Frame M, a rotation matrix.

   @verbatim
           M   S
   R_MS ≜    R
   @endverbatim

   The rotational velocity of Frame S measured in Frame M.

   @verbatim
            M ⟶ S
   w_MS  ≜    ω
   @endverbatim

   The rotational acceleration of Frame S measured in Frame M.

   @verbatim
                M ⟶ S      M   M ⟶ S      S   M ⟶ S
   alpha_MS  ≜    α    ≜     d   ω    =     d   ω
                          ───────────    ───────────
                               dt             dt
   @endverbatim

   @note When no "expressed in" frame is present, e.g. `w_MS`, then the "expressed in" frame is implicitly the
         "measured in" frame (i.e. `w_MS` equals `w_MS_M`).

   @verbatim
            ⎡ M ⟶ S ⎤      M ⟶ S
   w_MS_M = ⎣   ω   ⎦M  =    ω    = w_MS
   @endverbatim

   @subsection rotational-quantity-calculations Rotational Quantity Calculations

   @paragraph expressed-in-frames (Re)Expressing a quantity in a Frame
   The expressed in frame determines which vector basis the spatial quantity vector is written in (for example, êˣ, êʸ,
   êᶻ for expressed in frame, E).  Vector quantities can be "reexpressed" simply by left-multiplication with the
   relevent rotation matrix. For example, a rotational velocity that is expressed in Frame E is reexpressed in Frame M.
   @verbatim
                   M   E   ⎡ M ⟶ S ⎤     ⎡ M ⟶ S ⎤
   R_ME * w_MS_E =   R   * ⎣   ω   ⎦E  = ⎣   ω   ⎦M = w_MS_M
   @endverbatim

   @note Changes to the expressed-in frame for a spatial quantity, will never change the magnitude of that quantity
         (e.g. ||w_MS_E|| equals ||w_MS_M||, above).

   @note Reexpressing the frame of a vector quantity is an instantaneous operation; the motion of the expressed-in
         frame is not considered in time derivative calculations.

   Negating an angular velocity.
   @verbatim
            ⎡ M ⟶ S ⎤      ⎡ S ⟶ M ⎤
   w_MS_E = ⎣   ω   ⎦E  = -⎣   ω   ⎦E = -w_SM_E
   @endverbatim

   Adding angular velocities.
   @verbatim
   ⎡ M ⟶ S ⎤    ⎡ S ⟶ T ⎤    ⎡ M ⟶ T ⎤
   ⎣   ω   ⎦E + ⎣   ω   ⎦E = ⎣   ω   ⎦E
   @endverbatim

   @warning Adding angular acclerations.
   @verbatim
   ⎡ M ⟶ S ⎤    ⎡ S ⟶ T ⎤   [DOES NOT EQUAL] ⎡ M ⟶ T ⎤
   ⎣   α   ⎦E + ⎣   α   ⎦E         ≠         ⎣   α   ⎦E
   @endverbatim

   @section translational-quantities Translational Quantities

   @subsection translational-quantity-identities Translational Quantity Identities

   @paragraph The "golden rule of vector differentiation".
   Whenever you want to change the measured in frame for any vector differentiation (be it a position, velocity or any
   other vector), Just add ω x r, where r is the vector being differentiated.

   @verbatim
    A   Ap ⟶ Aq     B   Ap ⟶ Aq
      d    r          d    r        A ⟶ B     Ap ⟶ Aq
   ───────────── ≜ ───────────── +    ω    ⨯     r
        dt              dt
   @endverbatim

   @paragraph translational-offset The translational offset from the origin of Frame M to the origin of Frame S.

   @verbatim
              Mo ⟶ So
   p_MoSo_M ≜    r
   @endverbatim

   The translational velocity of Frame S measured in Frame M.

   @verbatim
            M ⟶ So    M   Mo ⟶ So
   v_MSo  ≜   v    ≜    d    r
                     ─────────────
                          dt
   @endverbatim

   The translational acceleration of Frame S measured in Frame M.

   @verbatim
            M ⟶ So    M   M ⟶ So
   a_MSo  ≜   a    ≜    d   v
                     ────────────
                          dt
   @endverbatim

   The translational velocity of Frame S relative to Frame R, measured in Frame M.

   @verbatim
               M ⟶ So/Ro    M   Ro ⟶ So
   v_M_RoSo  ≜   v       ≜    d    r
                           ─────────────
                                dt
   @endverbatim

   @verbatim
   ⎡ M ⟶ So/Ro ⎤     ⎡ M ⟶ So ⎤    ⎡ M ⟶ Ro ⎤
   ⎣   v       ⎦E  ≜ ⎣   v    ⎦E - ⎣   v    ⎦E
   @endverbatim

   The translational acceleration of Frame S relative to Frame R, measured in Frame M.

   @verbatim
               M ⟶ So/Ro    M    Ro ⟶ So
   a_M_RoSo  ≜   a       ≜    d²    r
                           ─────────────
                                dt²
   @endverbatim

   @verbatim
   ⎡ M ⟶ So/Ro ⎤     ⎡ M ⟶ So ⎤    ⎡ M ⟶ Ro ⎤
   ⎣   a       ⎦E  ≜ ⎣   a    ⎦E - ⎣   a    ⎦E
   @endverbatim

   @subsection translational-quantity-calculations Translational Quantity Calculations

   Shifting the measured frame for a translational velocity from Point So at a body's origin to an offset Point Sq
   affixed to the same body.

   @verbatim
   ⎡ M ⟶ Sq ⎤    ⎡ M ⟶ So ⎤    ⎡ M ⟶ S ⎤    ⎡ So ⟶ Sq ⎤
   ⎣   v    ⎦E ≜ ⎣   v    ⎦E + ⎣   ω   ⎦E ⨯ ⎣    r    ⎦E
   @endverbatim

   Shifting the measured frame for a translational acceleration from Point So at a body's origin to an offset Point Sq
   affixed to the same body.

   @verbatim
   ⎡ M ⟶ Sq ⎤    ⎡ M ⟶ So ⎤    ⎡ M ⟶ S ⎤    ⎡ So ⟶ Sq ⎤    ⎡ M ⟶ S ⎤    ⎛ ⎡ M ⟶ S ⎤    ⎡ So ⟶ Sq ⎤  ⎞
   ⎣   a    ⎦E ≜ ⎣   a    ⎦E + ⎣   α   ⎦E ⨯ ⎣    r    ⎦E + ⎣   ω   ⎦E ⨯ ⎝ ⎣   ω   ⎦E ⨯ ⎣    r    ⎦E ⎠
   @endverbatim

   Changing the measured-in frame of a relative translational velocity from "The translational velocity, measured in
   Frame M, of Frame S relative to Frame R" to "The translational velocity, measured in Frame N, of Frame S relative to
   Frame R"

   @verbatim
   ⎡ N ⟶ So/Ro ⎤    ⎡ M ⟶ So/Ro ⎤    ⎡ N ⟶ M ⎤    ⎡ Ro ⟶ So ⎤
   ⎣   v       ⎦E = ⎣   v       ⎦E + ⎣   ω   ⎦E ⨯ ⎣    r    ⎦E
   @endverbatim

   Changing the measured-in frame of a relative translational acceleration from "The translational acceleration of
   rame S relative to Frame R, measured in Frame M" to "The translational acceleration, measured in Frame N, of Frame S
   elative to Frame R"

   @verbatim
   ⎡ N ⟶ So/Ro ⎤    ⎡ M ⟶ So/Ro ⎤    ⎡ N ⟶ M ⎤    ⎡ Ro ⟶ So ⎤
   ⎣   a       ⎦E = ⎣   a       ⎦E + ⎣   α   ⎦E ⨯ ⎣    r    ⎦E

                      ⎡ N ⟶ M ⎤    ⎛ ⎡ N ⟶ M ⎤    ⎡ Ro ⟶ So ⎤  ⎞       ⎡ N ⟶ M ⎤    ⎡ M ⟶ So/Ro ⎤
                    + ⎣   ω   ⎦E ⨯ ⎝ ⎣   ω   ⎦E ⨯ ⎣    r    ⎦E ⎠ + 2 * ⎣   ω   ⎦E ⨯ ⎣   v       ⎦E
   @endverbatim

   @section spatial-quantities Spatial Quantities

   @subsection spatial-quantity-identities Spatial Quantity Identities

   Spatial quantities are stacked vectors containing a rotational component over a translational component.

   The spatial velocity of Frame Sa, measured in Frame M, expressed in Frame E.

   @verbatim
                           ╭─────────╮   ╭────────╮
             ⎡ M ⟶ Sa ⎤    │  w_MS_E │   │ M ⟶ S  │
   V_MSa_E = ⎣   V    ⎦E = ├┈┈┈┈┈┈┈┈┈┤ = │   ω    │
                           │ v_MSa_E │   ├┈┈┈┈┈┈┈┈┤
                           ╰─────────╯   │ M ⟶ Sa │
                                         │   v    │
                                         ╰────────╯E
   @endverbatim

   The spatial velocity, measured in in Frame M, of Frame Sa, relative to Frame Rb, and expressed in Frame E.

   @verbatim
                                 ╭────────────╮   ╭───────────╮
                ⎡ M ⟶ Sa/Rb ⎤    │     w_RS_E │   │   R ⟶ S   │
   V_M_RbSa_E = ⎣   V       ⎦E = ├┈┈┈┈┈┈┈┈┈┈┈┈┤ = │     ω     │
                                 │ v_M_RbSa_E │   ├┈┈┈┈┈┈┈┈┈┈┈┤
                                 ╰────────────╯   │ M ⟶ Sa/Rb │
                                                  │   v       │
                                                  ╰───────────╯E
   @endverbatim

   The spatial acceleration of Frame Sa, measured in Frame M, and expressed in Frame E.

   @verbatim
                           ╭────────────╮   ╭────────╮
             ⎡ M ⟶ Sa ⎤    │ alpha_MS_E │   │ M ⟶ S  │
   A_MSa_E = ⎣   A    ⎦E = ├┈┈┈┈┈┈┈┈┈┈┈┈┤ = │   α    │
                           │    a_MSa_E │   ├┈┈┈┈┈┈┈┈┤
                           ╰────────────╯   │ M ⟶ Sa │
                                            │   a    │
                                            ╰────────╯E
   @endverbatim

   The spatial acceleration, measured in in Frame M, of Frame Sa, relative to Frame Rb, and expressed in Frame E.

   @verbatim
                                 ╭────────────╮   ╭───────────╮
                ⎡ M ⟶ Sa/Rb ⎤    │ alpha_RS_E │   │   R ⟶ S   │
   A_M_RbSa_E = ⎣   A       ⎦E = ├┈┈┈┈┈┈┈┈┈┈┈┈┤ = │     α     │
                                 │ a_M_RbSa_E │   ├┈┈┈┈┈┈┈┈┈┈┈┤
                                 ╰────────────╯   │ M ⟶ Sa/Rb │
                                                  │   a       │
                                                  ╰───────────╯E
   @endverbatim
*/
