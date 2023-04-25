from django.urls import path
from services.views import home, signup, about, contact, supplier_register, SupplierList, menu, profile
from django.contrib.auth.views import LoginView, LogoutView

urlpatterns = [
    path('', LoginView.as_view(template_name="base.html"), name="login"),
    path('signup/', signup, name="signup"),
    path('home/', home, name="home"),
    path('profile/', profile, name="profile"),
    path('menu/', menu, name="menu"),
    path('supplier/', supplier_register, name="supplier"),
    path('supplier_list/', SupplierList.as_view(), name="supplierlist"),
    path('about/', about, name="about"),
    path('contact/', contact, name="contact"),
    path('cerrar/', LogoutView.as_view(), name="logout"),
]
