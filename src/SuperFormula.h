//
//// SuperFormula.h
//

#ifndef _SUPERFORMULA_
#define _SUPERFORMULA_

#include <cassert>
#include <cstring>
#include <Eigen/Core>
#include <Eigen/StdVector>
// import most common Eigen types
//USING_PART_OF_NAMESPACE_EIGEN
using namespace Eigen;
using namespace std;



class RationalSuperShape2D{

	public:

        // parameters of the rational supershape
        // Parameters[0] : a
        // Parameters[1] : b

        // Parameters[2] : n1
        // Parameters[3] : n2
        // Parameters[4] : n3

        // Parameters[5] : p
        // Parameters[6] : q

        // Parameters[7] : theta offset
        // Parameters[8] : phi offset // unused in 2D

        // Parameters[9] : x offset
        // Parameters[10] : y offset
        // Parameters[11] : z offset // unused in 2D

        vector<double> Parameters;

		//data storage for display
        vector< Vector3d, aligned_allocator< Vector3d> > PointList;
        vector< Vector3d, aligned_allocator< Vector3d> > NormalList;
        vector< Vector3i, aligned_allocator< Vector3i> > FaceList;

		//constructors an destructors
		RationalSuperShape2D();
		RationalSuperShape2D(double a, double b, double n1,double n2,double n3,double p, double q, double thtoffset=0, double phioffset=0, double xoffset=0, double y_offset=0, double zoffset=0);
		virtual ~RationalSuperShape2D();
		void Init( double a, double b, double n1,double n2,double n3,double p, double q, double thtoffset=0, double phioffset=0, double xoffset=0, double y_offset=0, double zoffset=0);
		void Init( double a, double b, double n1,double n2,double n3);

		//computation
		//double ImplicitFunction0(const Vector2d P, bool op=1, int m=1);
		double ImplicitFunction1( const Vector2d P, vector <double> &Dffinal );
		double ImplicitFunction2( const Vector2d P, vector <double> &Dffinal );
		double ImplicitFunction3( const Vector2d P, vector <double> &Dffinal );

        double DrDa(const double);
        double DrDb(const double);
        double DrDn1(const double);
        double DrDn2(const double);
        double DrDn3(const double);

        void GetPartialDerivatives(double tht, double &DrDa, double &DrDb, double &DrDn1, double &DrDn2, double &DrDn3);

        void Optimize5D(
            string outfilename, //file to store the evolution of the best fitted curve though iterations
            const vector< Vector2d, aligned_allocator< Vector2d> >, // array of 2D points
            double & ,         //error of fit
            int functionused = 1 //index of the implicit function used:1,2,or 3
            );

        void Optimize7D(
            string outfilename, //file to store the evolution of the best fitted curve though iterations
            const vector< Vector2d, aligned_allocator< Vector2d> >, // array of 2D points
            double & ,         //error of fit
            int functionused = 1 //index of the implicit function used:1,2,or 3
            );

        void Optimize8D(
            string outfilename, //file to store the evolution of the best fitted curve though iterations
            const vector< Vector2d, aligned_allocator< Vector2d> >, // array of 2D points
            double & ,         //error of fit
            int functionused = 1 //index of the implicit function used:1,2,or 3
            );

        //sub function used in the baove function to compute hessian approx and gradient
        double XiSquare5D(
                      const vector < Vector2d, aligned_allocator< Vector2d> > Data,    //array of 2D points
                      MatrixXd &alpha,      //hessian approximation
                      VectorXd &beta,       //gradient approximation
                      int function_used = 1,    //index of the implicit function used
                      bool udpate = false); //boolean if hessian and gradient have to be updated or not

        double XiSquare7D(
                      const vector < Vector2d, aligned_allocator< Vector2d> > Data,    //array of 2D points
                      MatrixXd &alpha,      //hessian approximation
                      VectorXd &beta,       //gradient approximation
                      int function_used = 1,    //index of the implicit function used
                      bool udpate = false); //boolean if hessian and gradient have to be updated or not

        double XiSquare8D(
                      const vector < Vector2d, aligned_allocator< Vector2d> > Data,    //array of 2D points
                      MatrixXd &alpha,      //hessian approximation
                      VectorXd &beta,       //gradient approximation
                      int function_used = 1,    //index of the implicit function used
                      bool udpate = false); //boolean if hessian and gradient have to be updated or not

		double radius ( const double angle );

		inline Vector2d Point( double angle) {double r = radius(angle); return Vector2d (r*cos(angle),r*sin(angle));};

        inline double Get_a()  {return Parameters [0];};
        inline double Get_b()  {return Parameters [1];};

        inline double Get_n1() {return Parameters [2];};
        inline double Get_n2() {return Parameters [3];};
        inline double Get_n3() {return Parameters [4];};

        inline double Get_p()  {return Parameters [5];};
        inline double Get_q()  {return Parameters [6];};

        inline double Get_thtoffset()  {return Parameters [7];};
        inline double Get_phioffset()  {return Parameters [8];};

        inline double Get_xoffset()  {return Parameters [9];};
        inline double Get_yoffset()  {return Parameters [10];};
        inline double Get_zoffset()  {return Parameters [11];};

        inline double Set_a ( const double a)  {Parameters [0]=fabs(a);};
        inline double Set_b ( const double b)  {Parameters [1]=fabs(b);};

        inline double Set_n1( const double n1) {Parameters [2]=fabs(n1);};
        inline double Set_n2( const double n2) {Parameters [3]=fabs(n2);};
        inline double Set_n3( const double n3) {Parameters [4]=fabs(n3);};

        inline double Set_p ( const double p)  {Parameters [5]=p;};
        inline double Set_q ( const double q)  {Parameters [6]=q;};

        inline double Set_thtoffset ( const double thtoffset)  {Parameters [7]=thtoffset;};
        inline double Set_phioffset ( const double phioffset)  {Parameters [8]=phioffset;};

        inline double Set_xoffset ( const double xoffset)  {Parameters [9]=xoffset;};
        inline double Set_yoffset ( const double yoffset)  {Parameters [10]=yoffset;};
        inline double Set_zoffset ( const double zoffset)  {Parameters [11]=zoffset;};


        double CurveLength(int n = 50);

        void Aff(); // stupid function to display params value
	// Guillaume stupid function 
	void writeFile(std::string fileName);

        double DrDtheta(double tht);


        //update Guillaume

        //first and second order approximation of the distance point to curve(tht) regarding tht
        inline double Deriv1(double tht, Vector2d P, double delta = 1e-3)
        {
        Vector4d V(
                  Distance (P, tht-2*delta),
                  -8*Distance (P, tht-delta),
                  8*Distance (P, tht+delta),
                  -Distance (P, tht+2*delta)
                  );

        return V.sum() / (12*delta);
        };

        inline double Deriv2(double theta, Vector2d P, double delta = 1e-3)
        {

        VectorXd V(5);
        V << -Distance (P, theta - 2*delta),
            16*Distance (P, theta - delta),
            -30*Distance (P, theta),
            16*Distance (P, theta + delta),
            -Distance (P, theta + 2*delta);

        return V.sum()/(12*delta*delta);
        };

        //distance between point and point (tht) on the curve:

        inline double Distance (Vector2d P, double tht)
        {
        //convert P in polar coordinates. P must be in canonical ref

        Vector2d Ppol(P.norm(), atan2(P[1],P[0]));
        if (Ppol[1]<0) Ppol[1] += 2*PI;

        double r (radius(tht));
        return sqrt( r*r + Ppol[0]*Ppol[0] - 2*r*Ppol[0]*cos(tht-Ppol[1]));

        };

        //variation of gauss newton algo for shortest distance computation
        Vector2d ClosestPoint( Vector2d P, int itmax = 10);

        //computation of the four cost functions for a given data set, returns Mean and Var for each cost function
        bool ErrorMetric (vector < Vector2d, aligned_allocator< Vector2d> > Data, Vector4d &Mean, Vector4d &Var);
};

inline std::ostream& operator<<(std::ostream& os, const RationalSuperShape2D& RS2D)
        {
        for(int i=0; i<RS2D.Parameters.size(); i++) os<<RS2D.Parameters[i]<<" ";
        os<<endl;
        return os;
        };

//Rfunction for self intersecting curves
void RpUnion(double f1, double f2, vector<double> Df1, vector<double> Df2, double &f, vector<double> &Df);
void RpIntersection(double f1, double f2, vector<double> Df1, vector<double> Df2, double &f, vector<double> &Df);

#endif
