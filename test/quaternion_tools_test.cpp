#include <gtest/gtest.h>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "quaternion_tools.h"

TEST(Quaternion, test_cross_matrix) {
    Eigen::Quaterniond q(1.0, 2.0, 3.0, M_PI); // random
    q.normalize();
    
    Eigen::Matrix3d r = q.toRotationMatrix();
    
    auto p1 = (q.w()*q.w() - q.vec().transpose()*q.vec())*Eigen::Matrix3d::Identity();
    auto p2 = 2*q.vec()*q.vec().transpose();
    auto p3 = 2*q.w()*QuaternionTools::crossMatrix(q.vec());
    auto r_from_q = p1 + p2 + p3;
    
    ASSERT_TRUE(r.isApprox(r_from_q));
}

TEST(Quaternion, test_big_omega_matrix) {
    Eigen::Quaterniond q(1.0, 2.0, 3.0, M_PI); // random
    q.normalize();
    
    Eigen::Vector3d perturb_vec;
    perturb_vec << 0.001, 0.02, -0.004;
    perturb_vec.normalize();
    
    Eigen::Vector4d q_as_vector;
    q_as_vector << q.w(), q.x(), q.y(), q.z();
    Eigen::Vector4d q_dot_vec = 0.5 * QuaternionTools::bigOmegaMatrix(perturb_vec) * q_as_vector;
    Eigen::Quaterniond q_lhs(q_dot_vec(0), q_dot_vec(1), q_dot_vec(2), q_dot_vec(3));
    
    Eigen::Quaterniond q_perturb(0.0, perturb_vec(0), perturb_vec(1), perturb_vec(2));
    Eigen::Quaterniond q_rhs = Eigen::Quaterniond(0.5, 0.0, 0.0, 0.0) * q * q_perturb;
    
    ASSERT_TRUE(q_lhs.isApprox(q_rhs));
    
//    Eigen::Vector3d qqq;
//    qqq << 1, 2, 3;
//    std::cout << QuaternionTools::bigOmegaMatrix(qqq) << std::endl << std::endl;
//    
//    std::cout << matrix_derivative << std::endl;
//    std::cout << quaternion_derivative.toRotationMatrix() << std::endl;
//    
//    ASSERT_TRUE(matrix_derivative.isApprox(quaternion_derivative.toRotationMatrix()));
//
//    ASSERT_TRUE(quaternion_derivative.toRo
//    
//    Eigen::Matrix3d r = q.toRotationMatrix();
//    
//    auto p1 = (q.w()*q.w() - q.vec().transpose()*q.vec())*Eigen::Matrix3d::Identity();
//    auto p2 = 2*q.vec()*q.vec().transpose();
//    auto p3 = 2*q.w()*QuaternionTools::crossMatrix(q.vec());
//    auto r_from_q = p1 + p2 + p3;
//    
//    ASSERT_TRUE(r.isApprox(r_from_q));
}
